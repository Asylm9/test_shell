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
/* L'ordre d'application des redirections lors de l'exécution :
- D'abord configurer les pipes (stdin/stdout entre les commandes)
- Ensuite appliquer les redirections locales de chaque commande */

int	execute_command(t_command *cmd, t_sh *shell)
{

	if (!cmd ||!cmd->cmd_name)
		return (0);
	if (is_builtin(cmd->cmd_name))
	{
		//builtins executes par processus parent
		//pas sure de la marche a suivre
		//voir comment fonctionnent builtins
		return (execute_builtin(cmd, shell));
	}
	else
		 return (execute_binary(cmd, shell->env));
}

int	setup_pipes_redirections(int **pipes, int nb_pipes, int i)
{
	if (i > 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0) //le premier pipe devient le stdin de la 2ere CMD (read end)
			return (1);
	}
	if (i < nb_pipes)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0) //idem avec stdin si pas derniere CMD (write end)
			return (1);
	}
	return (0);
}

int	wait_for_children(int nb_pipes, pid_t *pids)
{
	int	last_status;
	int	status;
	int	i;

	last_status = 0;
	i = 0;
	while (i <= nb_pipes)
	{
		waitpid(pids[i], &status, 0);
		if (i == nb_pipes)
		{
			if (WIFEXITED(status))
			{
				last_status = WEXITSTATUS(status);
				if (status != 0)
					exit(last_status);
			}
			if (WIFSIGNALED(status))
				last_status = (128 + WTERMSIG(status));
		}
		i++;
	}
	return (last_status);
}

int	execute_pipeline(t_command *cmd_list, t_sh *shell)
{
	int			nb_pipes;
	int			**pipes;
	pid_t		*pids;
	t_command	*current;
	int			i;

	get_pipe_count(cmd_list, &nb_pipes);
	pipes = create_pipes(nb_pipes);
	if (!pipes)
		return (1);
	pids = malloc(sizeof(pid_t) * (nb_pipes + 1));
	if (!pids)
	{
		close_pipes(pipes, nb_pipes);
		return (1);
	}
	current = cmd_list;
	i = 0;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			//CHILD PROCESS

			setup_pipes_redirections(pipes, nb_pipes, i);

			//ensuite redirections "locales"?
			apply_redirections(current);

			if (is_builtin(cmd_list->cmd_name))
				return (execute_builtin(cmd_list, shell));
			else
				return (execute_binary(cmd_list, shell->env));

		}
		current = current->next;
		i++;
	}
	close_pipes(pipes, nb_pipes);
	shell->exit_status = wait_for_children(nb_pipes, pids);
	free(pids);
	return (shell->exit_status);
}

int		execute(t_command *cmd_list, t_sh *shell)
{
	int	status;

	if (!cmd_list)
		return (0);
	if (cmd_list->next)
		status = execute_pipeline(cmd_list, shell);
	else
		status = execute_command(cmd_list, shell);
	shell->exit_status = status;
	return (status); //Le shell doit toujours mettre à jour et retourner le statut de la dernière commande exécutée.
}
