#include "minishell.h"

int	execute_pipeline(t_ast *ast, t_sh *shell)
{
	if (ast )
}

int	execute_command(t_command *cmd, t_sh *shell)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->cmd_name)) 
		return (execute_builtin(cmd, shell));
	pid = fork();
	if (pid < 0)
		return (ERROR);
	else if (pid == 0)
	{
		if (apply_redirections(cmd) == ERROR)
			exit(1);
/* 		if (is_builtin(cmd->cmd_name)) // jamais de fork! si redirection (sans pipeline)->save & restore fd pour ne pas alterer les stdin/out du shell
			exit(execute_builtin(cmd, shell)); */
		exit(execute_binary(cmd, shell->env));
	}
	waitpid(pid, &status, 0);
	return (process_wait_status(status));
}

int	execute_ast(t_ast *ast, t_sh *shell)
{
	int status;

	if (!ast)
		return (0);
	if (ast->type == CMD)
		return (execute_command(ast->cmd, shell));
	else if (ast->type == PIPE)
		return (execute_pipeline(ast, shell));
	return (0);
}
