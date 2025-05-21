#include "minishell.h"

void	init_cmd_struct(t_command *cmd, char *arg1, char **arg2)
{
	cmd->cmd_name = arg1;
	cmd->args = arg2;
	cmd->redirections = NULL;
}
