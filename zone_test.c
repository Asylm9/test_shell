/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:55:02 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/13 18:13:36 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*expand_token(char *input)
// {
// 	char	*result;
// 	char	*buffer;
// 	char	*tmp;
// 	int		pos;
// 	int		start;

// 	result = ft_calloc(1, 1);
// 	buffer = NULL;
// 	tmp = NULL;
// 	pos = 0;
// 	start = 0;
// 	while (input[pos] != '\0')
// 	{
// 		if (input[pos] == '$')
// 		{
// 			buffer = ft_substr(input, start, pos - start);
// 			if (tmp)
// 				free(tmp);
// 			tmp = ft_strjoin(result, buffer);
// 			free(buffer);
// 			buffer = expand_var(input + pos);
// 			if (buffer)
// 			{
// 				free(result);
// 				result = ft_strjoin(tmp, expand_var(input + pos));
// 			}
// 			pos++;
// 			while ((ft_isalnum(input[pos]) || input[pos] == '_') && input[pos])
// 				pos++;
// 			start = pos;
// 		}
// 		else
// 			pos++;
// 	}
// 	buffer = ft_substr(input, start, pos - start);
// 	free(result);
// 	result = ft_strjoin(tmp, buffer);
// 	free(tmp);
// 	free(buffer);
// 	return (result);
// }

int	is_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*result;
	int		i;

	str = ft_strdup("test abc def ghi $HOME hehe ouou");
	result = expand_token(str);
	printf("Result: |%s|\n", result);
	free(str);
	free(result);
	return (0);
}
// int i = 0;
// char *env;
// char *value = "test abc def ghi $HOME hehe ouou";
// int len = 0;
// char *cur_env;
// int exp_size;

// exp_size = expand_size("test abc def ghi /home/magoosse hehe ouou",
// envp);
// printf("exp size : %d\n", exp_size);

// while (value[len])
// {
// 	if (value[len] == '$')
// 	{
// 		while (value[len + i] && value[len + i] != ' ')
// 			i++;
// 		cur_env = ft_substr(value, len + 1, i - 1);
// 		printf("cur env : |%s|\n", cur_env);
// 		// env_prev_size += i;
// 		// if (getenv(env) == NULL)
// 		// 	env_expd_size -= i;
// 		// else
// 		// 	env_expd_size += ft_strlen();
// 	}
// 	len++;
// }

// // while (envp[i])
// // {
// // 	printf("Env %d : %s\n", i + 1, envp[i]);
// // 	i++;
// // }
// printf("len ABC :%ld\n", ft_strlen(ft_strdup(getenv(cur_env))));
// env = ft_strdup(getenv(cur_env));
// printf("env = %s\n", env);
// printf("%ld , %s\n", ft_strlen(env), ft_strnstr("(null)", "(null)",
// 6));

// printf("len : %ld, strnstr %s\n", ft_strlen(env), ft_strnstr(env,
// "(null)",
// 		ft_strlen(env)));