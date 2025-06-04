/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magoosse <magoosse@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:33:39 by magoosse          #+#    #+#             */
/*   Updated: 2024/11/01 18:56:23 by magoosse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;
	void	*a;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	elem = NULL;
	while (lst)
	{
		a = (*f)(lst->content);
		elem = ft_lstnew(a);
		if (!elem)
		{
			del(a);
			ft_lstclear(&new_lst, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	ft_lstclear(&lst, (*del));
	return (new_lst);
}
