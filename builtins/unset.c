#include "../minishell.h"

static	void delete_env_var(t_env *current, t_env **head)
{
	t_env	*prev;
	t_env	*next;

	prev = current->prev;
	next = current->next;
	prev->next = next;
	next->prev = prev;
	free(current->key);
	if (current->value)
		free(current->value);
	free(current);
/* 	printf("prev key: %s, prev value: %s\n", prev->key, prev->value);
	printf("next key: %s, next->value: %s\n", prev->next->key, prev->next->value);
	printf("\n---------------------------------------------\n");
	printf("next key: %s, next value: %s\n", next->key, next->value);
	printf("prev key: %s, prev->value: %s\n", next->key, next->value); */
}

int		builtin_unset(char **args, t_env **envl)
{
	t_env	*current;
	int		i;

	if (!args[1])
		return (SUCCESS); //ne se passe rien/retour de la ligne de commande
	i = 1;
	while (args[i])
	{
		current = *envl;
		while (current)
		{
			if (ft_strcmp(current->key, args[i]) == 0)
			{
				delete_env_var(current, envl);
				break;
			}
			current = current->next;
		}
		i++;
	}
	return (SUCCESS); // si variable non trouve return avec 0, pas d'erreur
}

