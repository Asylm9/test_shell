#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	expand_size(char *value, char **env)
{
	int		i;
	int		len;
	int		env_prev_size;
	int		env_expd_size;
	char	*cur_env;

	i = 0;
	len = 0;
	env_prev_size = 0;
	env_expd_size = 0;
	while (value[len])
	{
		if (value[len] == '$')
		{
			i = 0;
			while (value[len + i] && value[len + i] != ' ')
				i++;
			cur_env = ft_substr(value, len + 1, i - 1);
			env_prev_size += i;
			if (getenv(cur_env) == NULL)
				env_expd_size -= i;
			else
				env_expd_size += ft_strlen(ft_strdup(getenv(cur_env)));
		}
		if (i != 0)
			len += i;
		else
			len++;
	}
	printf("env prev : %d\n", env_prev_size);
	printf("env expd : %d\n", env_expd_size);
	env_expd_size = len - env_prev_size + env_expd_size + 1;
	return (env_expd_size);
}

char	*expand_var(char *str)
{
	int		i;
	char	*var;
	char	*result;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
	{
		i++;
	}
	var = ft_substr(str, 0, i);
	printf("var : |%s|\n", var);
	result = getenv(var + 1);
	printf("env : |%s|\n", result);
	free(var);
	return (result);
}

int	main(int ac, char **av, char **envp)
{
	char *result;
	char *input = "test1 abc $HOME test2 test3 $HOME test4"; // dans proto
	char *buffer;
	int pos;
	int start;
	result = NULL;
	pos = 0;
	start = 0;

	while (input[pos] != '\0')
	{
		if (input[pos] == '$')
		{
			buffer = ft_substr(input, start, pos);
			printf("BUFFER PRE JOIN : |%s|\n", buffer);
			if (expand_var(input + pos) != "(null)")
				result = ft_strjoin(buffer, expand_var(input + pos));
			while (input[pos] != ' ' && input[pos])
				pos++;
			start = pos;
		}
		else
			pos++;
		if (result)
			printf("BUFFER POST JOIN : |%s|\n", result);
	}
	printf("Result : |%s|\n", result);

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
	return (0);
}