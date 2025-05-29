#include "../minishell.h"

static char *set_new_path(char **args, t_sh *shell)
{
	char	*new_path;

	// if cd seul, ~, $HOME
	// cd - -> home + print pwd ??
	if (!args[1] || args[1][0] == '~') // ou chemin absolu vers home
	{
		new_path = get_env_var("HOME", shell->env);
	}
	// 

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
