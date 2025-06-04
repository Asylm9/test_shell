/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:30:41 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:26:57 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c > 64 && c < 91)
		c = c + 32;
	return (c);
}
/*
int	main(void)
{
	char a;
	unsigned char b;
	unsigned char c;

	a = 'A';
	b = 'B';
	c = 'c';

	printf("%c\n", tolower(a));
	printf("%c\n", tolower(b));
	printf("%c\n", tolower(c));
	printf("%c\n", ft_tolower(a));
	printf("%c\n", ft_tolower(b));
	printf("%c\n", ft_tolower(c));
}*/
