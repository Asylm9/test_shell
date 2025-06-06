#include "../minishell.h"

static int	validate_format_export(char **args, int i)
{
	int		j;
	int		count;

	if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
	{
		printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
		return (ERROR);
	}
	j = 0;
	while (args[i][j] && args[i][j] != '=')
	{
		if (!ft_isalnum(args[i][j]) && args[i][j] != '_')
		{
			printf_fd(2, "minishell: export: `%s': not a valid identifier\n", args[i]);
			return (ERROR);
		}
		j++;
	}
	return (SUCCESS);
}

static int	process_export_arg(char **args, int i, t_env **envl)
{
	char 	*equal_pos;
	char	*value;
	int		ret;

	equal_pos = ft_strchr(args[i], '=');
	if (!equal_pos)	
	{
		if (!get_envl_var(args[i], *envl))
			ret = add_new_entry(args[i], NULL, envl);
	}
	else
	{
		*equal_pos = '\0';
		value = equal_pos + 1;
		if (ft_strlen(value) == 0)
			ret = add_new_entry(args[i], EMPTY, envl);
		else
			ret = add_new_entry(args[i], value, envl);
		*equal_pos = '=';
	}
	if (ret != 0)
		return (ERROR);
	return(SUCCESS);
}

int	builtin_export(char **args, t_env **envl)
{
	int		i;

	if (!envl)
		return (ERROR); // verifier comportement
	if (args_count(args) == 1 )
	{
		print_exp_list(envl);
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{

		if (validate_format_export(args, i) != 0)
			return (ERROR);
		if (process_export_arg(args, i, envl) != 0)
			return (ERROR);
		i++;

		printf("\n---------------------------------\n");
		print_exp_list(envl);
	}
	return (SUCCESS);
}

