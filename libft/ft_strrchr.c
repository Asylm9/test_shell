/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:48:19 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:28:12 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	i = 0;
	b = (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			b = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (b);
}
/*
int	main(void)
{
	char a;
	char *b;

	a = '\0';
	b = "abdefghjiklmnopqrstuvwxyz";

	printf("%s\n", strrchr((b + 2), a));
	printf("%s\n", ft_strrchr((b + 2), a));
}*/
