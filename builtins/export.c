#include "../minishell.h"

int	validate_format_export(char **args, int i)
{
	int		j;
	int		count;
	bool	is_value;

	is_value = false;
	if (ft_isdigit(args[i][0]) || args[i][0] == '=')
	{
		printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
		return (ERROR);
	}
	count = 0;
	j = 0;
	while (args[i][j])
	{
		if (args[i][j] == '=')
			count += 1;
		if (count == 1)
			is_value = true;
		if (!is_value)
		{
			if (ft_isspec(args[i][j]) && args[i][j] != '=')
			{
				printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
				return (ERROR);
			}
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
	char *equal_pos;
	char	*key;
	char	*value;


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
			//key = ft_substr(args[i], 0, equal_pos - args[i]);
			//if (!key)
			//	return (ERROR);
			*equal_pos = '\0';
			value = equal_pos + 1;
			if (ft_strlen(value) == 0)
				add_new_entry(args[i], EMPTY, envl);
			else
				add_new_entry(args[i], value, envl);
			*equal_pos = '=';
			//free(key);
		}
		i++;
		printf("\n---------------------------------\n");
		print_exp_list(*envl);
	}
	return (SUCCESS);
}

/* int	builtin_export(char **args, t_env **envl)
{
	// exporexportt -> affiche env var par ordre ascii ainsi que var custom(valides ou non)
	//"export: not valid in this context:[arg]" code 1 -> verifier , ne retombe plus sur ce message: p-e zsh)
	// export permet de passer les variables crees (ou non) au futures chil processes -> only exported variables go into the process’s environment.
	int	i;
	char *equal_pos;
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
			printf("sub: %s\n", equal_pos);
			split = ft_split(args[i], '='); // attention cas: test== -> deuxieme '=' perdu !
			if (!split || !split[0])
				return (free(split), ERROR);
			else if (!split[1])
				add_new_entry(split[0], EMPTY, envl);
			else
				add_new_entry(split[0], split[1], envl);
			free_array(split, -1);
		}
		i++;
		printf("\n---------------------------------\n");
		print_exp_list(*envl);
	}
	return (SUCCESS);
} */

