/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:46:35 by magoosse          #+#    #+#             */
/*   Updated: 2025/03/28 17:12:21 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c || s[i] == '\n') && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_freeloc(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(*split);
	return (NULL);
}

static int	ft_stralloc(char *s, char c, char **result)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		count = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0' && s[i] != '\n')
		{
			i++;
			count++;
		}
		if (count > 0)
		{
			result[j++] = (char *)malloc(sizeof(char) * (count + 1));
			if (!result[j - 1])
				return (ft_freeloc(result, j), 0);
		}
	}
	return (result[j] = NULL, 1);
}

static void	ft_fill(char const *s, char c, char **split)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0' && s[i] != '\n')
			split[j][k++] = s[i++];
		if (split[j] != 0)
		{
			split[j++][k] = '\0';
			k = 0;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	if (ft_count((char *)s, c) <= 1)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_count((char *)s, c) + 1));
	if (!split)
		return (NULL);
	if (ft_stralloc((char *)s, c, split) == 0)
		return (split = NULL, NULL);
	ft_fill(s, c, split);
	return (split);
}

/*int	main(int ac, char **av)
{
	int		i;
	char	**split;

	(void)ac;
	i = 0;
	split = ft_split(av[1], av[2][0]);
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}*/
