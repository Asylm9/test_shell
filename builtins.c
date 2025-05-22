#include "minishell.h"

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

int		execute_builtin(t_command *cmd, t_sh *shell)
{
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
}