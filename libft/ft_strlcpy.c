/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:14:37 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:25:28 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	long int	j;

	i = 0;
	j = 0;
	while (i < dstsize - 1 && src[i] && dstsize != 0)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (dstsize != 0)
		((unsigned char *)dst)[i] = '\0';
	while (src[j])
		j++;
	return (j);
}
/*
int	main(void)
{
	char a[20];
	char b[] = "bonjour comment allez vous ?";
	char c[20];
	char d[] = "bonjour comment allez vous ?";

	printf("%lu\n", strlcpy(a, b, 0));
	printf("%zu\n", ft_strlcpy(c, d, 0));
	printf("%s\n", a);
	printf("%s\n", c);
}*/
