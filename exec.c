#include "minishell.h"

int	wait_for_children(int nb_pipes, pid_t *pids)
{
	int	last_status;
	int	status;
	int	i;

	last_status = 0;
	i = 0;
	while (i <= nb_pipes)
	{
		waitpid(pids[i], &status, 0);
		if (i == nb_pipes)
		{
			if (WIFEXITED(status)) //tue if child exit normally
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status)) //if interrupted by signal
				last_status = (128 + WTERMSIG(status)); //Return signal number that caused process to terminate.
		}
		i++;
	}
	return (last_status);
}

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

/* Ordre d'application des redirections lors de l'exécution :
- D'abord configurer les pipes (stdin/stdout entre les commandes)
- Ensuite appliquer les redirections locales de chaque commande */

int	execute_pipeline(t_command *cmd_list, t_sh *shell)
{
	int			nb_pipes;
	int			**pipes;
	pid_t		*pids;
	t_command	*current;
	int			i;

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
	current = cmd_list;
	i = 0;
	while (current)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			//CHILD PROCESS

			setup_pipes_redirections(pipes, nb_pipes, i);

			//ensuite redirections "locales"?
			apply_redirections(current);

			if (is_builtin(current->cmd_name))
				return (execute_builtin(current, shell));
			else
				return (execute_binary(current, shell->env));

		}
		current = current->next;
		i++;
	}
	close_pipes(pipes, nb_pipes);
	shell->exit_status = wait_for_children(nb_pipes, pids);
	free(pids);
	return (shell->exit_status);
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
