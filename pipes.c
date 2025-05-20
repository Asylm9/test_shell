#include "exec.h"

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

int	**create_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			free_pipes(pipes, i - 1);
		else if (pipes[i] < 0)
			free_pipes(pipes, i);
		return (NULL);
	}	
	return (pipes);
}

void	close_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	get_pipe_count(t_command *cmd_list, int *nb_pipes)
{
	nb_pipes = 0;
	while (cmd_list->next)
	{
		cmd_list = cmd_list->next;
		(*nb_pipes)++;
	}
}
