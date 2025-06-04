/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:54:08 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 19:18:49 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int a)
{
	int	count;

	count = 0;
	if (a <= 0)
		count++;
	while (a != 0)
	{
		a = a / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	nb;
	int			len;

	nb = n;
	len = ft_nbrlen(nb);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	if (nb < 0)
		nb = -nb;
	while (len > 0)
	{
		result[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n < 0)
		result[0] = '-';
	result[ft_nbrlen(n)] = '\0';
	return (result);
}
/*
int	main(void)
{
	int	a;

	a = -125;
	printf("%s\n", ft_itoa(a));
	int b;
	int c;

	b = 2147483647;
	c = -2147483648;

	
	printf("%s\n", ft_itoa(b));
	printf("%s\n", ft_itoa(c));
}
*/
