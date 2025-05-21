#include "minishell.h"

/* L'ordre d'application des redirections lors de l'exécution :
- D'abord configurer les pipes (stdin/stdout entre les commandes)
- Ensuite appliquer les redirections locales de chaque commande */

int	setup_pipes_redirections(int **pipes, int nb_pipes, int i)
{
	if (i > 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) < 0) //le premier pipe devient le stdin de la 2ere CMD (read end)
			return (1);
	}
	if (i < nb_pipes)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) < 0) //idem avec stdin si pas derniere CMD (write end)
			return (1);
	}
	return (0);
}

int	apply_redirections(t_command *cmd)
{
	t_redirect *redir;
	int	fd;

	if (!cmd->redirections)
		return (0); //pas d'erreur si pas de redirections
	redir = cmd->redirections;
	if (redir->type == IN)
	{
		fd = open(redir->target, O_RDONLY);
		if (fd < 0)
			return (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (redir->type == OUT)
	{
		fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == APPEND)
	{
		fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (redir->type == HEREDOC)
	{
		//voir comment heredoc fonctionne
	}
	return (0);
}