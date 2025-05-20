#include "exec.h"
#include "parsing.h"

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

int	init_pipes(int nb)
{
	int	pfd[nb][2];
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pfd) < 0)
			return (1);
	}	
	return (0);
}

void	pipe_nb(t_command *cmd_list, int *nb)
{
	int	nb;

	nb = 0;
	while (cmd_list->next)
	{
		cmd_list = cmd_list->next;
		nb++;
	}
}

int		execute(t_command *cmd_list, t_sh *shell)
{
	int	status;
	int	nb;

	if (!cmd_list)
		return (0);
	pipe_nb(cmd_list, &nb);
	init_pipes(nb);
	if (cmd_list->next)
		status = execute_pipeline(cmd_list, shell->env);
	else
		status = execute_command(cmd_list, shell->env);
	shell->exit_status = status;
	return (status);
}

/* Statut de sortie : Le shell doit toujours mettre à jour et retourner le statut de la dernière commande exécutée. */


int	apply_redirections(char *file, int pfd, int redirection)
{
	int	fd;

	if (REDIR_IN)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			close(pfd[0]);
			close(pfd[1]);
			return (1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		close(pfd[0]);
	}
	else if (REDIR_OUT)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			close(pfd[0]);
			close(pfd[1]);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(pfd[1]);
	}
	return (0);
}
