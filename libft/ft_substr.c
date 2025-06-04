/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:16:22 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:47:36 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;

	if (ft_strlen(s) - (start + 1) < len)
		len = ft_strlen(s) - start;
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result || start > ft_strlen(s))
		return (NULL);
	while (len--)
	{
		result[i++] = s[start++];
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void)
{
	char *a = ft_substr("hola", 4, 20);
	char *b = ft_substr("hola", 0, 1);
	char *c = ft_substr("hola", 0, 3);
	char *d = ft_substr("hola", 2, 0);
	char *e = ft_substr("hola", 2, 1);
	char *f = ft_substr("hola", 3, 0);

	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
	printf("%s\n", d);
	printf("%s\n", e);
	printf("%s\n", f);
}*/
