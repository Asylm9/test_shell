#include "../minishell.h"

int		builtin_unset(char **args, t_sh *shell)
{
	int		i;
	int		j;
	int		k;
	int		len;

	if (!args[1])
		return (SUCCESS); //ne se passe rien/retour de la ligne de commande
	i = 1;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		j = 0;
		while (shell->env[j])
		{
			if (ft_strncmp(shell->env[j], args[i], len) == 0 && shell->env[j][len] == '=')
			{
				free(shell->env[j]);
				while (shell->env[j + 1])
				{
					shell->env[j] = shell->env[j + 1];
					j++;
				}
				shell->env[j] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
	
	return (SUCCESS);
}
