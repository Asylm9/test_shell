/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:29:12 by magoosse          #+#    #+#             */
/*   Updated: 2025/06/13 17:43:32 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*result;

// 	i = 0;
// 	j = 0;
// 	if (ft_strlen(s1) + ft_strlen(s2) == 0)
// 		return (ft_strdup(""));
// 	len = (ft_strlen(s1) + ft_strlen(s2));
// 	result = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!result)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 		result[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i] != '\0')
// 		result[j++] = s2[i++];
// 	result[j] = '\0';
// 	return (result);
// }

char	*ft_strjoin(char const *s1, char const *s2, int flag)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	if (flag == 1)
		return (free((char *)s1), result);
	if (flag == 2)
		return (free((char *)s2), result);
	if (flag == 3)
		return (free((char *)s1), free((char *)s2), result);
	return (result);
}

/* int	main(void)
{
	char	*a;
	char	*b;
	char	*c;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup("Bonjour, ");
	tmp2 = ft_strdup("comment allez vous?");
	// a = ft_strjoin(tmp, tmp2, 3);
	b = ft_strjoin(tmp, tmp2, 3);
	// c = ft_strjoin(tmp, tmp2, 2);
	// c = ft_strjoin("Bonjour, ", "\0", 0);
	// char *d = ft_strjoin("Bonjour, ", "comment allez vous?");
	// char *e = ft_strjoin("Bonjour, ", "comment allez vous?");
	// char *f = ft_strjoin("Bonjour, ", "comment allez vous?");
	// char *g = ft_strjoin("Bonjour, ", "comment allez vous?");
	// printf("%s\n", a);
	printf("%s\n", b);
	// printf("%s\n", c);
	// free(a);
	free(b);
	// free(c);
} */
