#include "minishell.h"

char	*get_env_var(char *name, char **env)
{
	int	i;
	int	len;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_env = get_env_var("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_array(paths);
	return (full_path);
}

void	get_pipe_count(t_command *cmd_list, int *nb_pipes)
{
	t_command	*current;
	
	*nb_pipes = 0;
	current = cmd_list;
	while (current && current->next)
	{
		(*nb_pipes)++;
		current = current->next;
	}
}

int	**create_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			while (i >= 0)
			{
				free(pipes[i]);
				i--;
			}
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	apply_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			fd;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == IN)
		{
			fd = open(redir->target, O_RDONLY);
			if (fd < 0)
				return (1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redir->type == OUT)
		{
			fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == APPEND)
		{
			fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (1);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->type == HEREDOC)
		{
			// Heredoc should have been processed earlier with fd saved in redir->fd
			dup2(redir->fd, STDIN_FILENO);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0 ||
		ft_strcmp(cmd_name, "cd") == 0 ||
		ft_strcmp(cmd_name, "pwd") == 0 ||
		ft_strcmp(cmd_name, "export") == 0 ||
		ft_strcmp(cmd_name, "unset") == 0 ||
		ft_strcmp(cmd_name, "env") == 0 ||
		ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_command *cmd, t_sh *shell)
{
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		return (builtin_echo(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		return (builtin_export(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		return (builtin_exit(cmd->args, shell));
	return (1);
}

int	fork_binary_cmd(t_command *cmd, char **env)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	cmd_path = find_cmd_path(cmd->cmd_name, env);
	if (!cmd_path)
	{
		error_message("command not found");
		return (127);
	}
	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		error_message("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		if (apply_redirections(cmd) != 0)
			exit(1);
		execve(cmd_path, cmd->args, env);
		error_message("execve failed");
		exit(127);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	execute_command(t_command *cmd, t_sh *shell)
{
	if (!cmd || !cmd->cmd_name)
		return (0);
	
	// Check if it's a builtin command
	if (is_builtin(cmd->cmd_name))
	{
		// For a single command, we can execute builtins directly
		// But first, we need to handle redirections
		int stdin_copy = dup(STDIN_FILENO);
		int stdout_copy = dup(STDOUT_FILENO);
		
		if (apply_redirections(cmd) != 0)
			return (1);
		
		int result = execute_builtin(cmd, shell);
		
		// Restore standard input/output
		dup2(stdin_copy, STDIN_FILENO);
		dup2(stdout_copy, STDOUT_FILENO);
		close(stdin_copy);
		close(stdout_copy);
		
		return (result);
	}
	else
	{
		return (fork_binary_cmd(cmd, shell->env));
	}
}

int	execute_pipeline(t_command *cmd_list, t_sh *shell)
{
	t_command	*current;
	int			nb_pipes;
	int			**pipes;
	int			i;
	pid_t		*pids;
	int			status;
	int			last_status;

	get_pipe_count(cmd_list, &nb_pipes);
	pipes = create_pipes(nb_pipes);
	if (!pipes)
		return (1);
	
	pids = (pid_t *)malloc(sizeof(pid_t) * (nb_pipes + 1));
	if (!pids)
	{
		close_pipes(pipes, nb_pipes);
		return (1);
	}
	
	current = cmd_list;
	i = 0;
	
	// Execute commands in pipeline
	while (current)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			error_message("fork failed");
			break;
		}
		
		if (pids[i] == 0)
		{
			// Child process
			if (i > 0)
				dup2(pipes[i-1][0], STDIN_FILENO);
			
			if (i < nb_pipes)
				dup2(pipes[i][1], STDOUT_FILENO);
			
			// Close all pipe fds
			int j = 0;
			while (j < nb_pipes)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			
			// Apply command-specific redirections and execute
			if (apply_redirections(current) != 0)
				exit(1);
			
			// Dans un pipeline, nous exécutons les builtins comme des commandes:
			// Pas besoin de fork pour les builtins car on est déjà dans un processus enfant
			if (is_builtin(current->cmd_name))
				exit(execute_builtin(current, shell));
			else
			{
				char *cmd_path = find_cmd_path(current->cmd_name, shell->env);
				if (!cmd_path)
				{
					error_message("command not found");
					exit(127);
				}
				execve(cmd_path, current->args, shell->env);
				free(cmd_path);
				error_message("execve failed");
				exit(127);
			}
		}
		
		current = current->next;
		i++;
	}
	
	// Close all pipe fds in parent
	for (i = 0; i < nb_pipes; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
	
	// Wait for all children
	last_status = 0;
	for (i = 0; i < nb_pipes + 1; i++)
	{
		waitpid(pids[i], &status, 0);
		if (i == nb_pipes)  // Last command's status
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else
				last_status = 1;
		}
	}
	free(pids);
	
	return (last_status);
}

int	execute(t_command *cmd_list, t_sh *shell)
{
	int	status;

	if (!cmd_list)
		return (0);
	
	if (!cmd_list->next)
		status = execute_command(cmd_list, shell);
	else
		status = execute_pipeline(cmd_list, shell);
	
	shell->exit_status = status;
	return (status);
}

void	error_message(const char *msg)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}