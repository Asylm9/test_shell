
void	free_pipes(int **pipes, int i)
{
	if (!pipes)
		return;
	while (i >= 0)
		free(pipes[i]);
	free(pipes);
}

void	free_array(char *s, int i)
{
	if (!s)
		return;
	while (i >= 0)
		free(s[i]);
	free(s);
}
