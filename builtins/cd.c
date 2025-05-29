#include "../minishell.h"

int	args_count(char **args)
{
	int count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

// faire un arg count a la place d'utiliser les index dans les verifications?
static char *set_new_path(char **args, t_sh *shell)
{
	char	*new_path;
	int 	argc;

	new_path = NULL;
	argc = args_count(args);
	if (argc > 2)
		return(printf("minishell: cd: too many arguments\n"), NULL);
	if (argc == 1)
	{
		new_path = get_env_var("HOME", shell->env);
	}
	else if (argc == 2) // absolute_path~ deja traduit en chemin absolu vers home
	{
		new_path = args[1];
	}
	if (!new_path)
		printf("minishell: cd: HOME not set\n");

	// cd '-' -> OLDPWD 

	// root : cd / (dir) opt
	// curent_dir -> sub_dir: dir /
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

	builtin_pwd(shell);

	return (SUCCESS);
}
