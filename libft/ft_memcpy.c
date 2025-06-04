/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:18:15 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:23:19 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	
	unsigned char	a[10];
	unsigned char	b[] = "test\\200";
	unsigned char	c[10];
	unsigned char	d[] = "test\\200";
	
	memcpy(((void *)0), ((void *)0), 8);
	ft_memcpy(((void *)0), ((void *)0), 8);
	//a[4] = '\0';
	//c[4] = '\0';

	//printf("%s\n", a);
	//printf("%s\n", c);
	return (0);
}*/
