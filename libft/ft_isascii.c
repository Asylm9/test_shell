/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:23:49 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:14:00 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>
//#include <stdio.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
int	main(void)
{
	int a;
	char b;

	a = 9;
	b = 'q';

	printf("%d\n", isascii(a));
	printf("%d\n", isascii(b));
	printf("%d\n", ft_isascii(a));
	printf("%d\n", ft_isascii(b));
}*/
