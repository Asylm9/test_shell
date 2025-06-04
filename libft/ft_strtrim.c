/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:39:36 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:48:54 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_included(char s1, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		start;
	int		end;

	i = 0;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (ft_included(s1[i], (char *)set) && s1[i])
		i++;
	start = i;
	i = (ft_strlen(s1) - 1);
	while (ft_included(s1[i], (char *)set))
		i--;
	end = i;
	result = ft_substr(s1, start, (end - start + 1));
	return (result);
}
/*
int	main(void)
{
	char *s1 = "abcdefghiabc";
	char *s2 = "abcdefghi";
	char *s3 = "defghiabc";
	char *s4 = "";
	char *s5 = "\0";
	char *s6 = "abcabcabcabc";
	
	char *set1 = "abc";
	char *set2 = "";
	char *set3 = "\0";

	printf("%s\n", ft_strtrim(s1, set1));
	printf("%s\n", ft_strtrim(s2, set1));
	printf("%s\n", ft_strtrim(s3, set1));
	printf("%s\n", ft_strtrim(s4, set1));
	printf("%s\n", ft_strtrim(s5, set1));
	printf("%s\n", ft_strtrim(s6, set1));

	printf("%s\n", ft_strtrim(s1, set2));
	printf("%s\n", ft_strtrim(s2, set2));
	printf("%s\n", ft_strtrim(s3, set2));
	printf("%s\n", ft_strtrim(s4, set2));
	printf("%s\n", ft_strtrim(s5, set2));
	printf("%s\n", ft_strtrim(s6, set2));
	
	printf("%s\n", ft_strtrim(s1, set3));
	printf("%s\n", ft_strtrim(s2, set3));
	printf("%s\n", ft_strtrim(s3, set3));
	printf("%s\n", ft_strtrim(s4, set3));
	printf("%s\n", ft_strtrim(s5, set3));
	printf("%s\n", ft_strtrim(s6, set3));

	char *test1 = "lorem \n ipsum \t dolor \n sit \t amet";
	char *test2 = "lorem ipsum dolor sit amet";
	char *test3 = "lorem ipsum dolor sit amet";
	char *test4 = "lorem ipsum dolor sit amet";
	char *test5 = "             ";
	char *test6 = " \t \t \n   \n\n\n\t";

	char *t1 = " ";
	char *t2 = "te";
	char *t3 = "l";
	char *t4 = "tel";
	char *t5 = " \n\t";

	printf("\nTESTS : \n");
	printf("%s\n", ft_strtrim(test1, t1));
	printf("%s\n", ft_strtrim(test2, t2));
	printf("%s\n", ft_strtrim(test3, t3));
	printf("%s\n", ft_strtrim(test4, t4));
	printf("%s\n", ft_strtrim(test5, t1));
	printf("%s\n", ft_strtrim(test6, t5));
}*/
