#include "minishell.h"

int	builtin_export(char **args, t_env **envl)
{
	int		i;
	char	**split;
	char	*equal_pos;

	if (!envl)
		return (ERROR);
	
	if (args_count(args) == 1)
	{
		print_exp_list(*envl);
		return (SUCCESS);
	}

	i = 1;
	while (args[i])
	{
		if (validate_format_export(args, i) != SUCCESS)
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
			split = ft_split(args[i], '=');
			if (!split || !split[0])
			{
				free_array(split, -1);
				return (ERROR);
			}
			
			// split[1] peut être NULL si args[i] se termine par '='
			if (set_envl_var(split[0], envl, split[1]) != SUCCESS)
			{
				free_array(split, -1);
				return (ERROR);
			}
			
			free_array(split, -1);
		}
		i++;
	}
	return (SUCCESS);
}

int	builtin_export(char **args, t_env **envl)
{
	int		i;
	char	**split;
	char	*key;
	char	*value;
	char	*equal_pos;
	int		key_len;

	if (!envl)
		return (ERROR);
	
	if (args_count(args) == 1)
	{
		print_exp_list(*envl);
		return (SUCCESS);
	}

	i = 1;
	while (args[i])
	{
		if (validate_format_export(args, i) != SUCCESS)
			return (ERROR);

		equal_pos = ft_strchr(args[i], '=');
		
		if (!equal_pos)
		{
			key = ft_strdup(args[i]);
			if (!key)
				return (ERROR);
			
			if (!get_envl_var(key, *envl))
			{
				if (add_new_entry(key, NULL, envl) != SUCCESS)
				{
					free(key);
					return (ERROR);
				}
			}
			else
			{
				// Variable existe déjà, on garde sa valeur actuelle
				free(key);
			}
		}
		else
		{
			// Avec '=', séparer key et value
			key_len = equal_pos - args[i];
			key = ft_substr(args[i], 0, key_len);  // ou malloc + ft_strlcpy
			value = ft_strdup(equal_pos + 1);
			
			if (!key || !value)
			{
				free(key);
				free(value);
				return (ERROR);
			}
			
			// Utiliser set_envl_var qui gère ajout/modification
			if (set_envl_var(key, envl, value) != SUCCESS)
			{
				free(key);
				free(value);
				return (ERROR);
			}
			
			// set_envl_var fait ses propres strdup, on peut libérer
			free(key);
			free(value);
		}
		i++;
	}
	return (SUCCESS);
}

int	add_new_entry(char *key, char *value, t_env **envl)
{
	t_env	*new_node;
	char	*key_copy;
	char	*value_copy;

	// Faire des copies des chaînes
	key_copy = ft_strdup(key);
	if (!key_copy)
		return (ERROR);
	
	value_copy = NULL;
	if (value)
	{
		value_copy = ft_strdup(value);
		if (!value_copy)
		{
			free(key_copy);
			return (ERROR);
		}
	}

	new_node = create_node(key_copy, value_copy);
	if (!new_node)
	{
		free(key_copy);
		free(value_copy);
		return (ERROR);
	}
	*envl = add_back_node(new_node, *envl);
	return (SUCCESS);
}

int	set_envl_var(char *name, t_env **envl, char *value)
{
	t_env	*current;

	if (!name || !envl)
		return (ERROR);
	
	current = *envl;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
		{
			// Variable trouvée, mettre à jour sa valeur
			free(current->value);
			current->value = value ? ft_strdup(value) : NULL;
			if (value && !current->value)
				return (ERROR);
			return (SUCCESS);
		}
		current = current->next;
	}
	
	// Variable non trouvée, l'ajouter
	return (add_new_entry(name, value, envl));
}