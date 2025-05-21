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
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	**get_paths(char **env)
{
	char	*env_path;
	char	**paths;

	env_path = get_env_var("PATH", env);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	return (paths);
}

static char	*is_absolute(char *cmd)
{
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL); // ou exit?
	}
	return (NULL);
}

char	*find_cmd_path(char **paths, char *cmd_name)
{
	char	*test_path;
	int		i;

	if (!paths)
		return (NULL);
	if (is_absolute(cmd_name))
		return (cmd_name);
	i = 0;
	while (paths[i])
	{
		test_path = ft_pathjoin(paths[i], cmd_name);
		if (!test_path)
			return (NULL);
		if (access(test_path, F_OK | X_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}

int	execute_binary(t_command *cmd, char **env)
{
	char	**paths;
	char	*cmd_path;

	if (!cmd || !env)
		return (1);
	paths = get_paths(env);
	if (!paths)
		return (1);
	cmd_path = find_cmd_path(paths, cmd->cmd_name);
	free_array(paths, -1);
	if (!cmd_path)
		return (1);
	if (execve(cmd_path, cmd->args, env) < 0)
	{
		free(cmd_path);
		perror("execve");
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_command	cmd;

	if (ac != 3)
		return (1);
	printf("main 1");
	init_cmd_struct(&cmd, av[1], &av[1]);
	printf("main 2");
	execute_binary(&cmd, envp);
	return (0);
}
