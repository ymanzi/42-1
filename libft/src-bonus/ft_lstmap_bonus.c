/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:43:36 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 17:43:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"
#include <stdio.h>
#include <string.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_list;
	t_list *next_old;
	t_list *next_new;

	CHECK_PTR(lst);
	CHECK_PTR(new_list = ft_lstnew((*f)(lst->content)));
	next_new = new_list;
	next_old = lst->next;
	while (1)
	{
		if (next_old == NULL)
			break ;
		CHECK_PTR(next_new->next = ft_lstnew((*f)(next_old->content)));
		next_new = next_new->next;
		next_old = next_old->next;
	}
	if (del != NULL)
		ft_lstclear(&lst, del);
	return (new_list);
}
