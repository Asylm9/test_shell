#include "../minishell.h"

int	builtin_env(t_sh *shell)
{
	int	i;

	if (!shell || !shell->env) // Error: no environment variables found
		return (BUILTIN_ERR);
	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
	return (SUCCESS);
}
