#include "../minishell.h"

int	builtin_export(char **args, t_env **envl)
{
	// export -> affiche env var par ordre ascii ainsi que var custom(valides ou non)
	//"export: not valid in this context:[arg]" code 1 -> verifier , ne retombe plus sur ce message: p-e zsh)
	// export permet de passer les variables crees (ou non) au futures chil processes -> only exported variables go into the process’s environment.
	int	i;
	int	j;

	if (!envl)
		return (ERROR); // verifier comportement
	if (args_count(args) == 1 )
		print_exp_list(*envl);
	i = 1;
	if (ft_isspec(args[i][0]) || ft_isdigit(args[i][0]))
	{
		printf_fd(2, "minishell: export: `%c': not a valid identifier\n", args[i][0]);
		return (ERROR);
	}
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (ft_isspec(args[i][j]))
			{
				printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
				return (ERROR);
			}
			j++;
		}
		// add_new_entry(, true);
		i++;
	}
	return (SUCCESS);
}

// minishell: export: `9ekwlfhk': not a valid identifier
// bash: export: `/ekwlfhk': not a valid identifier
// bash: export: `bettera#ve': not a valid identifier

