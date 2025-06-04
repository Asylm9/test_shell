/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:57:18 by magoosse          #+#    #+#             */
/*   Updated: 2025/03/17 15:37:38 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(long int a)
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

void	ft_putnbr(int n, size_t *count)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		nb = -nb;
	}
	if (nb < 10)
	{
		ft_putchar_fd(nb + '0', 1);
	}
	else
	{
		ft_putnbr_fd((nb / 10), 1);
		ft_putchar_fd((nb % 10) + '0', 1);
	}
	*count += ft_nbrlen(n);
}

void	ft_putuns(unsigned int n, size_t *count)
{
	if (n < 10)
		ft_putchar_fd(n + '0', 1);
	else
	{
		ft_putnbr_fd((n / 10), 1);
		ft_putchar_fd((n % 10) + '0', 1);
	}
	*count += ft_nbrlen(n);
}

void	ft_printhex(unsigned long long n, size_t *count, char *base)
{
	if (n < 16)
	{
		ft_putchar_fd(base[n % 16], 1);
		(*count)++;
	}
	else
	{
		ft_printhex((n / 16), count, base);
		ft_putchar_fd(base[n % 16], 1);
		(*count)++;
	}
}

int	ft_hexlen(unsigned long n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}
