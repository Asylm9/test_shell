/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:30:03 by magoosse          #+#    #+#             */
/*   Updated: 2025/04/20 21:52:44 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	neg;
	long	buffer;
	long	result;

	i = 0;
	neg = 1;
	result = 0;
	buffer = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		result = (result * 10) + (str[i++] - '0');
		if (buffer > result && neg > 0)
			return (-1);
		buffer = result;
	}
	return (result * neg);
}

/*
int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	char	*d;
	char	*e;
	char	*f;
	char	*s;
	char	*t;
	int		g;
	int		h;
	int		i;
	int		j;
	int		k;
	int		l;
	int		u;
	int		w;
	int		m;
	int		n;
	int		o;
	int		p;
	int		q;
	int		r;
	int		v;
	int		x;

	a = " ";
	b = "\t\v\f\r\n \f-06050";
	c = "2147483647";
	d = "-2147483648";
	e = "9223372036854775809879847";
	f = "-92233720368549498498775807";
	s = "   -2147483652";
	t = "+2147483647";
	g = atoi(a);
	h = atoi(b);
	i = atoi(c);
	j = atoi(d);
	k = atoi(e);
	l = atoi(f);
	u = atoi(s);
	w = atoi(t);
	m = ft_atoi(a);
	n = ft_atoi(b);
	o = ft_atoi(c);
	p = ft_atoi(d);
	q = ft_atoi(e);
	r = ft_atoi(f);
	v = ft_atoi(s);
	x = ft_atoi(t);
	printf("Atoi : %d\n", g);
	printf("Ft   : %d\n", m);
	printf("Atoi : %d\n", h);
	printf("Ft   : %d\n", n);
	printf("Atoi : %d\n", i);
	printf("Ft   : %d\n", o);
	printf("Atoi : %d\n", j);
	printf("Ft   : %d\n", p);
	printf("Atoi : %d\n", k);
	printf("Ft l  : %d\n", q);
	printf("Atoi : %d\n", l);
	printf("Ft   : %d\n", r);
	printf("Atoi : %d\n", u);
	printf("Ft   : %d\n", v);
	printf("Atoi : %d\n", w);
	printf("Ft   : %d\n", x);
}
 */