#include "minishell.h"

// doublon a supprimer apres tests
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
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}
int	builtin_pwd(t_sh *shell)
{
	char	buffer[PATH_MAX];

	if (!getcwd(buffer, sizeof(buffer))) //normalement  present dans limits.h
	{
		perror("getcwd");
		return (BUILTIN_ERR);
	}
	printf("%s\n", buffer);
	return (SUCCESS);
}

/* int	builtin_pwd(char **envp)
{
	char	*pwd;

	pwd = get_env_var("PWD", envp);
	printf("%s\n", pwd);
} */

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
}

int		execute_builtin(t_command *cmd, t_sh *shell)
{
	// shell->exit_code a la place de return?
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		return (builtin_echo(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		return (builtin_export(cmd->args, shell->env));
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		return (builtin_unset(cmd->args, shell));
re} */

int	main(int ac, char **av, char **envp)
{
	builtin_pwd(envp);
	return (0);
}