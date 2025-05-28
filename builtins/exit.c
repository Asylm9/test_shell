#include "../minishell.h"

static bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit((arg[i])))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(char **args, t_sh *shell)
{	
	int	code;

	printf("exit\n");
	if (!args[1])
		code = shell->exit_status;
	else
	{
		code = ft_atoi(args[1]);
		if (!is_numeric(args[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			code = BUILTIN_ERR; //quitte avec code erreur 2
		}
		else if (args[1] && args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (ERROR); //retourne l'invite de commande
		}
	/* 	if (code > 25) -> se fait automatiquement dans exit()
			code %= 256; */
	}
	exit(code);
	return (SUCCESS);
}
