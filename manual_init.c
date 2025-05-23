#include "minishell.h"

void init_redir(t_redirect *redir)
{
	redir->type = IN;
	redir->target = "/home/agaland/19Cursus/rank3/test_shell/file.txt";
	redir->fd = -1;
}

void	init_cmd_struct(t_command *cmd, char **av, t_redirect *redir)
{
	cmd->cmd_name = av[1];
	cmd->args = av;
	cmd->redirections = redir;
}

void	init_shell_struct(t_sh *shell, char **envp)
{
	shell->env = envp;
}
