/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:25:45 by magoosse          #+#    #+#             */
/*   Updated: 2025/04/01 17:38:31 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	is_line(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*b;

	i = 0;
	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	b = (unsigned char *)malloc(size * count);
	if (!b)
		return (NULL);
	while (i < count * size)
		b[i++] = 0;
	return ((void *)b);
}

void	ft_free(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
