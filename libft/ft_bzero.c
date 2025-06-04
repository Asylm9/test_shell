/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:33:25 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:17:44 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	int		i;
	size_t	n;
	char tab[100];
	ft_memset(tab, 'A', 100);
	//int		s[8] = {12, 15, 20, 31, 26, 58, 100, 17};
	//int		z[8] = {12, 15, 20, 31, 26, 58, 100, 17};

	i = 0;
	n = 42;
	ft_bzero((void *)tab, n);
	//bzero(s, n);
	//ft_bzero(z, n);
	while (i < 100)
	{
		//printf("%d\n", s[i]);
		printf("%c\n", tab[i]);
		i++;
	}
}*/
