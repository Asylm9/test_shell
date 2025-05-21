#include "minishell.h"

void	free_pipes(int **pipes, int i)
{
	if (!pipes)
		return;
	while (i >= 0)
		free(pipes[i--]);
	free(pipes);
}

void	free_array(char **array, int i)
{
	if (!array)
		return;
	if (i < 0)
	{
		i = 0;
		while (array[i])
			free(array[i++]);
	}
	else 
	{
		while (i >= 0)
			free(array[i--]);
	}
	free(array);
}
