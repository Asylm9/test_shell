/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:36:39 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:54:49 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
/*
int	main(void)
{
	t_list	*test;

	test = ft_lstnew_bonus((void *)42);
	test->next = ft_lstnew_bonus((void *)56);
	test->next->next = ft_lstnew_bonus((void *)420);
	while (test)
	{
		printf("%d\n", (int)test->content);
		test = test->next;
	}
}*/
