/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:22:11 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:26:38 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	char a;
	unsigned char b;
	unsigned char c;

	a = 'a';
	b = 'b';
	c = 'C';

	printf("%c\n", toupper(a));
	printf("%c\n", toupper(b));
	printf("%c\n", toupper(c));

	printf("%c\n", ft_toupper(a));
	printf("%c\n", ft_toupper(b));
	printf("%c\n", ft_toupper(c));
}*/
