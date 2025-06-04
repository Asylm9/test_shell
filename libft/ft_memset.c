/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:59:57 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:17:07 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len > 0)
	{
		p[len - 1] = (unsigned char)c;
		len--;
	}
	return (b);
}
/*
int	main(void)
{
	size_t len;
	
	char b[6];
	char c[6];
	len = 4;
	memset(b, '1', len);
	ft_memset(c, '1', len);
	int	i = 0;
	while (i < 6)
	{
		printf("%c\n", b[i]);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		printf("%c\n", c[i]);
		i++;
	}
}*/
