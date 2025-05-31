#include "../minishell.h"

int	args_count(char **args)
{
	int count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

char	*relative_path(char **args, t_sh *shell)
{
	char	**asplit;
	char 	*new_path;
	char	*temp;
	int		i;

	asplit = ft_split(args[1], '/');
	if (!asplit)
		return (NULL);
	i = 0;
	while (asplit[i])
	{
		if (ft_strcmp(asplit[i], ".") == 0)
		{
			if (i == 0)
				new_path = get_env_var("PWD", shell->env);
		}		
		else if (ft_strcmp(asplit[i], "..") == 0)
		{
			if (i == 0)
				temp = get_env_var("PWD", shell->env);
			else
				temp = new_path;
			new_path =  reverse_trim(temp, "/");
		}
		else
			new_path = ft_pathjoin(new_path, asplit[i]);
		i++;
	}
	free_array(asplit, -1);
	return (new_path);
}

static char *set_new_path(char **args, t_sh *shell)
{
	char	*new_path;
	int 	argc;
	int		i;

	new_path = NULL;
	argc = args_count(args);
	if (argc > 2)
		return(printf("minishell: cd: too many arguments\n"), NULL);
	if (argc == 1)
		new_path = get_env_var("HOME", shell->env);
	else if (argc == 2) // absolute_path ~ deja traduit en chemin absolu vers home
	{
		if (args[1][0] == '-')
			new_path = get_env_var("OLDPWD", shell->env);
		if (args[1][0] != '/')
			new_path = relative_path(args, shell);
		else
			new_path = args[1];
	}
	if (!new_path)
		printf("minishell: cd: HOME not set\n");
	if (access(new_path, F_OK | X_OK) < 0)
	{
		printf("cd: no such file or directory: %s\n", new_path);
		return (NULL);
	}
	return (new_path);
}

int	builtin_cd(char **args, t_sh *shell)
{
	char	buffer[PATH_MAX];
	char	*new_path;

	// recuperer current_path
	if (!getcwd(buffer, sizeof(buffer))) 
	{
		perror("getcwd");
		return (BUILTIN_ERR);
	}
	// rechercher le new_path
	new_path = set_new_path(args, shell);
	if (!new_path)
		return (ERROR);
	// changer current directory
	if (chdir(new_path) < 0)
		return (BUILTIN_ERR);
	// actualiser OLDPWD avec current
	set_env_var("OLDPWD", shell->env, buffer);
	if (!getcwd(buffer, sizeof(buffer))) 
	{
		perror("getcwd");
		return (BUILTIN_ERR);
	}
	// actualiser PWD avec current
	set_env_var("PWD", shell->env, buffer);
	return (SUCCESS);
}
