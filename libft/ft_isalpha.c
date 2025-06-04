/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:36:55 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:13:31 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>
//#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

/*
int	main(void)
{
	unsigned int	a;
	unsigned char 	b;

	a = 'a';
	b = 'b';
	printf("%d\n", isalpha(a));
	printf("%d\n", isalpha(b));

	printf("%d\n", ft_isalpha(a));
	printf("%d\n", ft_isalpha(b));
}*/
