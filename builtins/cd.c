#include "../minishell.h"

static char *set_new_path(char **args, t_sh *shell)
{
	char	*new_path;
	int 	argc;
	int		i;

	new_path = NULL;
	argc = args_count(args);
	if (argc > 2)
		return(printf_fd(STDERR, "minishell: cd: too many arguments\n"), NULL);
	if (argc == 1)
		new_path = get_env_var("HOME", shell->env);
	else if (argc == 2)
	{
		if (args[1][0] == '-')
			new_path = get_env_var("OLDPWD", shell->env);
		else
			new_path = (args[1]);
	}
	return (new_path);
}

int	validate_path(char **args, char *new_path)
{
	int	argc;

	argc = args_count(args);
	if (!new_path)
	{
		if (argc == 1)
			printf_fd(STDERR, "minishell: cd: HOME not set\n");
		else if (args[1][0] == '-')
			printf_fd(STDERR, "minishell: cd: OLDPWD not set\n");
		else
			printf_fd(STDERR, "minishell: cd: invalid path\n");
		return (ERROR);
	}
	if (access(new_path, F_OK | X_OK) < 0)
	{
		printf_fd(STDERR, "cd: no such file or directory: %s\n", new_path);
		return (ERROR);
	}
	return (SUCCESS);
}

int update_pwds(t_sh *shell, char *curr_dir)
{
	// actualiser OLDPWD avec current
	set_env_var("OLDPWD", shell->env, curr_dir);
	if (!getcwd(curr_dir, PATH_MAX)) 
		return (perror("getcwd"), BUILTIN_ERR);
	// actualiser PWD avec current
	set_env_var("PWD", shell->env, curr_dir);
	return (SUCCESS);
}

int	builtin_cd(char **args, t_sh *shell)
{
	char	curr_dir[PATH_MAX];
	char	*new_path;

	if (!args)
		return (ERROR);
	// recuperer current_path
	if (!getcwd(curr_dir, PATH_MAX))
		return (perror("getcwd"), BUILTIN_ERR);
 	// rechercher le new_path
	new_path = set_new_path(args, shell);
	if (validate_path(args, new_path) != SUCCESS)
		return (ERROR);
	// changer current directory
	if (chdir(new_path) < 0)
		return (free(new_path), BUILTIN_ERR);
	if (update_pwds(shell, curr_dir) != 0)
		return (BUILTIN_ERR);
	return (SUCCESS);
}
