#include "../minishell.h"

int	args_count(char **args)
{
	int count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

bool state_changing_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	return (ft_strcmp(cmd_name, "cd") == 0 ||
			ft_strcmp(cmd_name, "export") == 0 ||
			ft_strcmp(cmd_name, "unset") == 0 ||
			ft_strcmp(cmd_name, "exit") == 0);
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

int		execute_builtin(t_command *cmd, t_sh *shell)
{
	t_env	envl;

	if (!cmd || !shell)
		return (ERROR); 
	
	// shell->exit_code a la place de return?
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		shell->exit_status = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		shell->exit_status = builtin_cd(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		shell->exit_status = builtin_pwd(shell);
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		shell->exit_status = builtin_export(cmd->args, &shell->envl);
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		shell->exit_status = builtin_unset(cmd->args, &shell->envl);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		shell->exit_status = builtin_env(shell);
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		shell->exit_status = builtin_exit(cmd->args, shell);
	return (shell->exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_sh		shell;
	t_command	cmd;

	if (ac < 2)
		return (0);
	init_shell_struct(&shell, envp);
	init_cmd_struct(&cmd, &av[1], NULL);

	//builtin_env(&shell);
	printf("\n-------------EXP-----------------\n");
	execute_builtin(&cmd, &shell);
	printf("\n-------------ENV-----------------\n");
	builtin_env(&shell);

	cleanup_shell(&shell);
	return (shell.exit_status);
}
