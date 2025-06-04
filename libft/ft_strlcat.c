/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:38:21 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:26:08 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	k;

	i = 0;
	j = 0;
	k = 0;
	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	while (dst[i++] && dstsize != 0)
		k++;
	i = 0;
	while (dst[i])
		i++;
	while (src[j] && i < dstsize - 1 && dstsize != 0)
		dst[i++] = src[j++];
	dst[i] = '\0';
	i = 0;
	while (src[i++])
		k++;
	return (k);
}
/*
int	main(void)
{
	char a[15] = "a";
	//memset(a, 'r', 15);
	char b[] = "lorem ipsum dolor sit amet";
	//char c[] = "hello";
	char d[15] = "a";
	//memset(d, 'r', 15);
	char e[] = "lorem ipsum dolor sit amet";
	//char f[] = "hello";

	printf("%lu\n", strlcat(a, b, 4));
	//printf("%lu\n", strlcat(a, c, 19));
	printf("%lu\n", ft_strlcat(d, e, 4));
	//printf("%lu\n", ft_strlcat(d, f, 19));
	printf("%s\n", a);
	printf("%s\n", d);
}*/
