#include "../minishell.h"

// doublon a supprimer apres tests
char	*get_env_var(char *name, char **env)
{
	int		i;
	int		len;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	set_env_var(char *name, char **env, char *value)
{
	int		i;
	int		len;
	char	*key;
	char	*new_value;

	if (!name || !env)
		return (ERROR);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			key = ft_strjoin(name, "=");
			if (!key)
				return (ERROR);
			new_value = ft_strjoin(key, value);
			if (!new_value)
			{
				free(key);
				return (ERROR);
			}
			free(key);
			env[i] = new_value;
			return (SUCCESS);
		}
		i++;
	}
	// key non trouvee
	return (ERROR);
}


/* bool	is_builtin(char *cmd_name)
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
} */

int		execute_builtin(t_command *cmd, t_sh *shell)
{
	// shell->exit_code a la place de return?
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		shell->exit_status = builtin_echo(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		shell->exit_status = builtin_cd(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		shell->exit_status = builtin_pwd(shell);
/* 	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		shell->exit_status = builtin_export(cmd->args, shell); */
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		shell->exit_status = builtin_unset(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		shell->exit_status = builtin_env(shell);
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		shell->exit_status = builtin_exit(cmd->args, shell);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sh		shell;
	t_command	cmd;
	int			i;

	i = 0;
	init_shell_struct(&shell, envp);
	init_cmd_struct(&cmd, &av[1], NULL);
/* 	while (av[i])
	{
		printf("args cmd: %s\n", cmd.args[i]);
		i++;
	} */
	execute_builtin(&cmd, &shell);
	cleanup_shell(&shell);
	return (shell.exit_status);
}