# include "minishell.h"

t_env	*init_env_list(char **env)
{
	char	**var;
	t_env	*new_node;
	t_env	*head;
	int		i;

	if (!env)
		return (NULL);
	head = NULL;
	i = 0;
	while (env[i])
	{
		var = ft_split(env[i], '=');
		if (!var)
			return (NULL);
		if (var[1])
			new_node = create_node(ft_strdup(var[0]), ft_strdup(var[1]));
		else
			new_node = create_node(ft_strdup(var[0]), NULL);
		if (!new_node)
			return (NULL);
		free_array(var, -1);
		head = add_back_node(new_node, head);
		i++;
	}
	return (head);
}

char	*get_env_var(char *name, char **env)
{
	int		i;
	int		len;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

int	set_env_var(char *name, char **env, char *value)
{
	int		i;
	int		len;
	char	*key;
	char	*new_value;

	if (!name || !env)
		return (ERROR);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			key = ft_strjoin(name, "=");
			if (!key)
				return (ERROR);
			new_value = ft_strjoin(key, value);
			if (!new_value)
			{
				free(key);
				return (ERROR);
			}
			free(key);
			env[i] = new_value;
			return (SUCCESS);
		}
		i++;
	}
	// key non trouvee
	return (ERROR);
}

/* int	set_env_var(char *name, char **env, char *value)
{
	int		i;
	char	*key;
	char	*new_value;

	if (!name || !env)
		return (ERROR);
	i = 0;

	if (key_found(name, env))
	{

	}
	else
		add_new_entry(name, value, env);
	return (ERROR);
}

int	add_new_entry(char *name, char *value, char **env)
{

}

bool	key_found(char *name, char **env)
{
	int		i;
	int		len;

	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && env[i][len] == '=')
			retun(true);
		i++;
	}
		while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			key = ft_strjoin(name, "=");
			if (!key)
				return (ERROR);
			new_value = ft_strjoin(key, value);
			if (!new_value)
			{
				free(key);
				return (ERROR);
			}
			free(key);
			env[i] = new_value;
			return (SUCCESS);
		}

		i++;
	}
	return (false);
} */