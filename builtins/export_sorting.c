#include "../minishell.h"

/* Compter le nombre de variables d'environnement */

int	count_elements(t_env *envl)
{
	t_env	*current;
	int		n;

	current = envl;
	n = 0;
	while (current)
	{
		current = current->next;
		n++;
	}
	return (n);
}

t_env	**init_temp_array(t_env *envl, int count)
{
	t_env **ptr_array;
	int		i;

	ptr_array = (t_env **) malloc(sizeof(t_env *) * count);
	if (!ptr_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ptr_array[i] = envl;
		envl = envl->next;
		i++;
	}
	return (ptr_array);
}

void	selection_sort(t_env **array, int count)
{
	int		i;
	int		j;
	int		min_index;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(array[j]->key, array[min_index]->key) < 0)
				min_index = j;
			j++;
		}
		if (min_index != i)
		{
			temp = array[i];
			array[i] = array[min_index];
			array[min_index] = temp;
		}
		i++;
	}
}
