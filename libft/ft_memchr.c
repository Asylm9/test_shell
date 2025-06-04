/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:03:26 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:30:02 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long	i;
	const char		*z;

	i = 0;
	z = (const char *) s;
	while (i < n)
	{
		if ((unsigned char)z[i] == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	c;
	char *s;

	c = 'a';
	s = "mmmmagnifique";
	printf("%s\n", memchr(s, c, 10));
	printf("%s\n", ft_memchr(s, c, 10));
}*/
