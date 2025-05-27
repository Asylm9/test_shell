#include "../minishell.h"

int	builtin_env(t_sh *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->env) // Error: no environment variables found
		return (BUILTIN_ERR);
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], 1);
		return (SUCCESS);
}
