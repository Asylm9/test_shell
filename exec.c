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
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
/* L'ordre d'application des redirections lors de l'exécution :
- D'abord configurer les pipes (stdin/stdout entre les commandes)
- Ensuite appliquer les redirections locales de chaque commande */

int	execute_command(t_command *cmd, t_sh *shell)
{

	if (!cmd ||!cmd->cmd_name)
		return (0);
	if (is_builtin(cmd->cmd_name))
	{
		//builtins executes par processus parent
		//pas sure de la marche a suivre
		//voir comment fonctionnent builtins
		return (execute_builtin(cmd, shell));
	}
	else
		 return (execute_binary(cmd, shell->env));
}

int	execute_pipeline(t_command *cmd_list, t_sh *shell)
{
	int		nb_pipes;
	int		**pipes;
	pid_t	*pids;

	get_pipe_count(cmd_list, &nb_pipes);
	pipes = create_pipes(nb_pipes);
	if (!pipes)
		return (1);
	pids = malloc(sizeof(pid_t) * (nb_pipes + 1));
	if (!pids)
	{
		close_pipes(pipes, nb_pipes);
		return (1);
	}
	return (0);
}

int		execute(t_command *cmd_list, t_sh *shell)
{
	int	status;

	if (!cmd_list)
		return (0);
	if (cmd_list->next)
		status = execute_pipeline(cmd_list, shell);
	else
		status = execute_command(cmd_list, shell);
	shell->exit_status = status;
	return (status); //Le shell doit toujours mettre à jour et retourner le statut de la dernière commande exécutée.
}


