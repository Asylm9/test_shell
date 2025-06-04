/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:19:22 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:24:24 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst != NULL || src != NULL)
	{
		while (len--)
		{
			if (dst > src)
			{
				((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
			}
			else
			{
				((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
				i++;
			}
		}
	}
	return (dst);
}
/*
int	main(void)
{
	char a[10];
	char b[] = "Bonjour";
	char c[10];
	char d[] = "Bonjour";

	memmove(a, b, 4);
	ft_memmove(c, d, 4);
	printf("%s\n", a);
	printf("%s\n", c);
}*/
