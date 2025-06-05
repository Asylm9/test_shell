#include "../minishell.h"

int	validate_format_export(char **args, int i)
{
	int	j;

	if (ft_isdigit(args[i][0]) || args[i][j] == '=')
	{
		printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
		return (ERROR);
	}
	j = 0;
	while (args[i][j])
	{
		if (ft_isspec(args[i][j]) && args[i][j] != '=')
		{
			printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
			return (ERROR);
		}
		j++;
	}
	return (SUCCESS);
}

int	builtin_export(char **args, t_env **envl)
{
	// exporexportt -> affiche env var par ordre ascii ainsi que var custom(valides ou non)
	//"export: not valid in this context:[arg]" code 1 -> verifier , ne retombe plus sur ce message: p-e zsh)
	// export permet de passer les variables crees (ou non) au futures chil processes -> only exported variables go into the process’s environment.
	int	i;
	char **split;
	if (!envl)
		return (ERROR); // verifier comportement
	if (args_count(args) == 1 )
	{
		print_exp_list(*envl);
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{

		if (validate_format_export(args, i) != 0)
			return (ERROR);
		if (!ft_strchr(args[i], '='))
			add_new_entry(args[i], NULL, *envl);
		else
			add_new_entry(args[i], args[i+1], envl);
			
		i++;
		printf("\n---------------------------------\n");
		print_exp_list(*envl);
	}
	return (SUCCESS);
}
