#include "../minishell.h"

int	builtin_cd(char **args, t_sh *shell)
{
	char *home;
	// chdir()

	if (!args[1])
	{
		home = get_env_var("HOME", shell->env);
		printf("home=%s\n", home);
	}
	// back to home : cd, ~, $HOME

	// root : cd / (dir) opt

	// curent_dir -> sub_dir: dir /
}
