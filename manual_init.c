#include "minishell.h"

void	init_cmd_struct(t_command *cmd, char *arg1, char **av)
{
	cmd->cmd_name = arg1;
	cmd->args = av;
	cmd->redirections = NULL;
}
