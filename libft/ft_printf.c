/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:30:30 by magoosse          #+#    #+#             */
/*   Updated: 2025/03/17 15:56:43 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_format(va_list ptr, char *str, size_t *count)
{
	if (*str == 'c')
		ft_putchar_count(va_arg(ptr, int), count);
	else if (*str == 's')
		ft_putstr(va_arg(ptr, char *), count);
	else if (*str == 'p')
		ft_putptr(va_arg(ptr, unsigned long), count);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr(va_arg(ptr, int), count);
	else if (*str == 'u')
		ft_putuns(va_arg(ptr, unsigned int), count);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'x')
			ft_printhex(va_arg(ptr, unsigned int), count, HEX_LOW_BASE);
		else
			ft_printhex(va_arg(ptr, unsigned int), count, HEX_UPP_BASE);
	}
	else if (*str == '%')
		ft_putchar_count('%', count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	size_t	count;

	va_start(ptr, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(ptr, (char *)str, &count);
		}
		else
			ft_putchar_count(*str, &count);
		str++;
	}
	va_end(ptr);
	return (count);
}
