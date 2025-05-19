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

int		execute_ast(t_command *cmd_list, t_sh *shell)
{
	int	status;

	if (!cmd_list)
		return (0);
	if (cmd_list)
		status = execute_pipeline(cmd_list, shell->env);
	else
		status = execute_command(cmd_list, shell->env);
	shell->exit_status = status;
	return (status);
}

/* Statut de sortie : Le shell doit toujours mettre à jour et retourner le statut de la dernière commande exécutée. */
