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
	char	*all_paths;
	char	**separate_paths;

	all_paths = NULL;
	if (!cmd)
		return (NULL);
	all_paths = get_env_var("PATH", env);
	if (!all_paths)
		return (NULL);
	separate_paths = ft_split(all_paths, ':');
	free(all_paths);
	return (separate_paths);
}