/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:28:02 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/26 14:01:46 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	{
		b[i] = 0;
		i++;
	}
	return ((void *)b);
}
/*
int	main(void)
{
	char *b;
	char *c;
	int	i;

	i = 0;
	b = (char *)calloc(10, 0);
	c = (char *)ft_calloc(10, 0);
	while (i < 15)
	{
		printf("%d\n", b[i]);
		i++;
	}
	i = 0;
	printf(" ft : \n");
	while (i < 15)
	{
		printf("%d\n", b[i]);
		i++;	
	}
}*/
