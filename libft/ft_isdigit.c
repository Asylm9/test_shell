/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:48:47 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:13:39 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>
//#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int a;
	char b;

	a = 1;
	b = '2';

	printf("%d\n", isdigit(a));
	printf("%d\n", isdigit(b));
	printf("%d\n", ft_isdigit(a));
	printf("%d\n", ft_isdigit(b));
}*/
