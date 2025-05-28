#include "../minishell.h"

int	builtin_cd(char **args, t_sh *shell)
{
	char *new_pwd;

	// chdir()

	if (!args[1])
	{
		new_pwd = get_env_var("HOME", shell->env);
		printf("home=%s\n", new_pwd);
	}
	// back to home : cd, ~, $HOME

	// root : cd / (dir) opt

	// curent_dir -> sub_dir: dir /
}
