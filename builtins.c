#include "minishell.h"

// doublon a supprimer apres tests
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
int	builtin_pwd(t_sh *shell)
{
	char	buffer[PATH_MAX]; //normalement present dans limits.h

	if (!getcwd(buffer, sizeof(buffer))) 
	{
		perror("getcwd");
		return (BUILTIN_ERR);
	}
	ft_putendl_fd(buffer, 1);
	return (SUCCESS);
}

int	builtin_env(t_sh *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->env) // Error: no environment variables found
		return (BUILTIN_ERR);
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], 1);
		return (SUCCESS);
}

static bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit((arg[i])))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(char **args, t_sh *shell)
{	
	int	code;

	printf("exit\n");
	if (!args[1])
		code = shell->exit_status;
	else
	{
		if (!is_numeric(args[1]))
		{
			printf("bash: exit: %s: numeric argument required", args[1]);
			code = BUILTIN_ERR; //quitte avec code erreur 2
		}
		else if (args[1] && args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (ERROR); //retourne l'invite de commande
		}
		code = ft_atoi(args[1]);
	/* 	if (code > 25) -> se fait automatiquement dans exit()
			code %= 256; */
	}
	exit(code);
	return (SUCCESS);
}

int	builtin_echo(char **args, t_sh *shell)
{
	int		i;
	int		j;
	bool	newline;
                                                       
	if (!args[1])
		return (BUILTIN_ERR);
	newline = true;
	i = 1;
	while ((ft_strncmp(args[i], "-n", 2)) == 0)
	{
		j = 2;
		while(args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}

int		builtin_unset(char **args, t_sh *shell)
{
	bool	found;
	int		i;
	int		j;
	int		len;

	if (!args[1])
		return (SUCCESS); //ne se passe rien/retour de la ligne de commande
	i = 1;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		j = 0;
		while (shell->env[j])
		{
			if (ft_strncmp(shell->env[j], args[i], len) == 0 && shell->env[j][len] == '=')
			{
				free(shell->env[j]);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	builtin_cd(char **args, t_sh *shell)
{
	// chdir()
	// back to home : cd, ~, $HOME

	// root : cd / (dir) opt

	// curent_dir -> sub_dir: dir /
}

/* int	builtin_pwd(char **envp)
{
	char	*pwd;

	pwd = get_env_var("PWD", envp);
	printf("%s\n", pwd);
} */

/* bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "echo") == 0 ||
		ft_strcmp(cmd_name, "cd") == 0 ||
		ft_strcmp(cmd_name, "pwd") == 0 ||
		ft_strcmp(cmd_name, "export") == 0 ||
		ft_strcmp(cmd_name, "unset") == 0 ||
		ft_strcmp(cmd_name, "env") == 0 ||
		ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}

int		execute_builtin(t_command *cmd, t_sh *shell)
{
	// shell->exit_code a la place de return?
	if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		return (builtin_echo(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		return (builtin_cd(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		return (builtin_pwd(shell));
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		return (builtin_export(cmd->args, shell->env));
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (builtin_unset(cmd->args, shell));
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		return (builtin_env(shell));
	else if (ft_strcmp(cmd->cmd_name, "exit") == 0)
		return (builtin_unset(cmd->args, shell));
} */

int	main(int ac, char **av, char **envp)
{
	t_sh		shell;
	t_command	cmd;	

	init_shell_struct(&shell, envp);
	init_cmd_struct(&cmd, &av[1], NULL);
	//builtin_pwd(&shell);
	builtin_env(&shell);
	//builtin_echo(cmd.args, &shell);
	//builtin_exit(cmd.args, &shell);
	builtin_unset(cmd.args, &shell);
	return (0);
}