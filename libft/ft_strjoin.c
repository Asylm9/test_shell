/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:29:12 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:48:07 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		return (ft_strdup(""));
	len = (ft_strlen(s1) + ft_strlen(s2));
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}
/*
int	main(void)
{
	char *a = ft_strjoin("\0", "comment allez vous?");
	char *b = ft_strjoin("Bonjour, ", "comment allez vous?");
	char *c = ft_strjoin("Bonjour, ", "\0");
	//char *d = ft_strjoin("Bonjour, ", "comment allez vous?");
	//char *e = ft_strjoin("Bonjour, ", "comment allez vous?");
	//char *f = ft_strjoin("Bonjour, ", "comment allez vous?");
	//char *g = ft_strjoin("Bonjour, ", "comment allez vous?");

	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
}*/
