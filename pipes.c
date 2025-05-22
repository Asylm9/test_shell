#include "minishell.h"

void	get_pipe_count(t_command *cmd_list, int *nb_pipes)
{
	t_command	*current;

	*nb_pipes = 0;
	current = cmd_list;
	while (current->next)
	{
		(*nb_pipes)++;
		cmd_list = cmd_list->next;
	}
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

int	init_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipes");
			free_pipes(pipes, i); //
			return (1);
		}
		i++;
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
		{
			free_pipes(pipes, i - 1);
			return (NULL);
		}
		i++;
	}
	if (init_pipes(pipes, nb_pipes) == 1)
		return (NULL);
	return (pipes);
}

