/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:55:02 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:29:25 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n == 0)
		return (0);
	if (s1[i] == '\0' || s2[i] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*a;
	char	*b;

	a = "abcdefgh";
	b = "";
	printf("%d\n", strncmp(a, b, 0));
	printf("%d\n", strncmp(a, b, 15));
	printf("%d\n", strncmp(a, b, 30));
	printf("%d\n", ft_strncmp(a, b, 0));
	printf("%d\n", ft_strncmp(a, b, 15));
	printf("%d\n", ft_strncmp(a, b, 30));
}*/
