/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_txt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:14:27 by magoosse          #+#    #+#             */
/*   Updated: 2025/03/17 15:55:30 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_count(char n, size_t *count)
{
	write(1, &n, 1);
	(*count)++;
}

void	ft_putstr(char *str, size_t *count)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		*count += 6;
	}
	else
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
			(*count)++;
		}
	}
}

void	ft_putptr(unsigned long ptr, size_t *count)
{
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		*count += 5;
	}
	else
	{
		ft_putstr("0x", count);
		ft_printhex(ptr, count, HEX_LOW_BASE);
	}
}
