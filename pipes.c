#include "minishell.h"

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
