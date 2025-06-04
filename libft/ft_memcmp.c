/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:44:36 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 20:45:10 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1)
	{
		if (p1[i] != p2[i])
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return ((unsigned char)p1[i] - (unsigned char)p2[i]);
}
/*
int	main(void)
{
	char *a = "Hello";
	char *b = "";
	char *c = "";
	char *d = "perruche";

	printf("%d\n", memcmp(a, b, 5));
	printf("%d\n", ft_memcmp(a, b, 5));
	printf("%d\n", memcmp(c, d, 12));
	printf("%d\n", ft_memcmp(c, d, 12));
}*/
