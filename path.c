#include "minishell.h"

char	*get_env_var(char *name, char **env)
{
	int	i;
	int	len;

	if (!name || !env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=') //attention verifier logique
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	*env_path;
	char	**paths;

	env_path = NULL;
	if (!cmd)
		return (NULL);
	env_path = get_env_var("PATH", env);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	return (paths);
}

