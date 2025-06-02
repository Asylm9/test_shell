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
			last_status = process_wait_status(status);
		i++;
	}
	return (last_status);
}

int	execute_command(t_command *cmd, t_sh *shell)
{
	pid_t	pid;
	int		status;

	if (!cmd ||!cmd->cmd_name)
		return (0);
	if (is_builtin(cmd->cmd_name))
		return (execute_builtin(cmd, shell));
	pid = fork();
	if (pid < 0)
		return (ERROR);
	else if (pid == 0)
	{
		if (apply_redirections(cmd) == ERROR)
			exit(1);
		status = execute_binary(cmd, shell->env);
		exit(status);
	}
	waitpid(pid, &status, 0);
	return (process_wait_status(status));
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

			if (setup_pipes_redirections(pipes, nb_pipes, i) == ERROR)
			{
				perror("dup2");
				exit(1);
			}
			close_pipes(pipes, nb_pipes); // didju sans fermer les pipes les processus attendent indéfiniment des données qui n'arriveront jamais → boucle infinie!
			//ensuite redirections "locales"
			if (apply_redirections(current) == ERROR)
				exit(1);
			if (is_builtin(current->cmd_name))
				return (execute_builtin(current, shell));
			else
				exit(execute_binary(current, shell->env));
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

	//init_env_list(shell->env);

	if (!cmd_list)
		return (0);
	if (cmd_list->next)
		status = execute_pipeline(cmd_list, shell);
	else
		status = execute_command(cmd_list, shell);
	shell->exit_status = status;
	return (shell->exit_status ); //Le shell doit toujours mettre à jour et retourner le statut de la dernière commande exécutée.
}

/* int	main(int ac, char **av, char **envp)
{
	t_command	cmd;
	//t_redirect	redir;
	int			status;

	status = 0;
	if (ac < 2)
		return (0);
	//init_redir(&redir);
	init_cmd_struct(&cmd, &av[1], NULL);
	status = execute_binary(&cmd, envp);
	return (status);
} */
