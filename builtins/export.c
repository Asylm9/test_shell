#include "../minishell.h"

int	validate_format_export(char **args, int i, int *count)
{
	int	j;
	count;

	if (ft_isdigit(args[i][0]) || args[i][0] == '=')
	{
		printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
		return (ERROR);
	}
	j = 0;
	while (args[i][j])
	{
		if (ft_strchr(args[i][j], '='))
			count++;
		if ((ft_isspec(args[i][j]) && args[i][j] != '=') || count > 1)
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
	int count;
	char *equal_pos;
	char **pair;

	if (!envl)
		return (ERROR); // verifier comportement
	if (args_count(args) == 1 )
	{
		print_exp_list(*envl);
		return (SUCCESS);
	}
	i = 1;
	count = 0;
	while (args[i])
	{

		if (validate_format_export(args, i, &count) != 0)
			return (ERROR);
		equal_pos = ft_strchr(args[i], '=');
		if (!equal_pos)	
		{
			if (!get_envl_var(args[i], *envl))
			{
					if (add_new_entry(args[i], NULL, envl) != SUCCESS)
						return (ERROR);
			}
		}
		else
		{
			pair = ft_split(args[i], '='); 
			if (!pair || !pair[0])
				return (free(pair), ERROR);
			else if (!pair[1])
				add_new_entry(pair[0], "", envl);
			else
				add_new_entry(pair[0], pair[1], envl);
			free_array(pair, -1);
		}
		i++;
		printf("\n---------------------------------\n");
		print_exp_list(*envl);
	}
	return (SUCCESS);
}
