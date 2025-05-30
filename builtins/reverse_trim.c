#include "../minishell.h"

static int	is_trim(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*reverse_trim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	start = 0;
	end = len - 1;
	while (end > start && (!is_trim(s1[end], set)))
		end--;
	res = (char *) malloc((end - start + 2) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[start], (end - start + 2));
	return (res);
}