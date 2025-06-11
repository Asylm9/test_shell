/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:09:51 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/11 15:19:47 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(char *str)
{
	int		i;
	char	*var;
	char	*result;

	i = 1;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	var = ft_substr(str, 0, i);
	result = getenv(var + 1);
	free(var);
	return (result);
}

char	*expand_token(char *input)
{
	char	*result;
	char	*buffer;
	char	*tmp;
	int		pos;
	int		start;

	result = ft_calloc(1, 1);
	buffer = NULL;
	tmp = NULL;
	pos = 0;
	start = 0;
	while (input[pos] != '\0')
	{
		if (input[pos] == '$')
		{
			buffer = ft_substr(input, start, pos - start);
			tmp = ft_strjoin(result, buffer);
			free(result);
			free(buffer);
			buffer = expand_var(input + pos);
			if (buffer)
			{
				result = ft_strjoin(tmp, buffer);
				free(tmp);
				// Do NOT free buffer if it comes from getenv!
			}
			else
			{
				free(result);
				result = tmp;
			}
			pos++;
			while ((ft_isalnum(input[pos]) || input[pos] == '_') && input[pos])
				pos++;
			start = pos;
		}
		else
			pos++;
	}
	buffer = ft_substr(input, start, pos - start);
	tmp = ft_strjoin(result, buffer);
	free(result);
	free(buffer);
	result = tmp;
	return (result);
}

t_token	*expand_list(t_token *tok_lst, char **env)
{
	t_token	*current;
	t_token	*head;
	char	*expanded_value;
	int		i;

	i = 0;
	current = malloc(sizeof(t_token));
	if (!current)
		return (NULL);
	head = current;
	while (tok_lst->value != NULL)
	{
		printf("test1\n");
		current->expand = NO_EXPAND;
		printf("test1.5\n");
		if (tok_lst->expand == NO_EXPAND)
		{
			current->value = ft_strdup(tok_lst->value);
			if (!current->value)
			{
				free(current);
				return (NULL);
			}
		}
		else
		{
			printf("|%s| test2\n", tok_lst->value);
			current->value = expand_token(tok_lst->value);
			printf("|%s| test3\n", current->value);
		}
		current->type = tok_lst->type;
		printf("|%d| test3\n", current->type);
		current->next = malloc(sizeof(t_token));
		printf("test4\n");
		tok_lst = tok_lst->next;
		if (tok_lst != NULL)
			current = current->next;
		printf("test4.5\n");
	}
	printf("test5\n");
	printf("Head value : %s\n", head->value);
	return (head);
}

// int	expand_size(char *value, char **env)
// {
// 	int		i;
// 	int		len;
// 	int		env_prev_size;
// 	int		env_expd_size;
// 	char	*cur_env;

// 	i = 0;
// 	len = 0;
// 	env_prev_size = 0;
// 	env_expd_size = 0;
// 	while (value[len])
// 	{
// 		if (value[len] == '$')
// 		{
// 			i = 0;
// 			while (value[len + i] && value[len + i] != ' ')
// 				i++;
// 			cur_env = ft_substr(value, len + 1, i - 1);
// 			env_prev_size += i;
// 			if (getenv(cur_env) == NULL)
// 				env_expd_size -= i;
// 			else
// 				env_expd_size += ft_strlen(ft_strdup(getenv(cur_env)));
// 		}
// 		if (i != 0)
// 			len += i;
// 		else
// 			len++;
// 	}
// 	printf("env prev : %d\n", env_prev_size);
// 	printf("env expd : %d\n", env_expd_size);
// 	env_expd_size = len - env_prev_size + env_expd_size + 1;
// 	return (env_expd_size);
// }