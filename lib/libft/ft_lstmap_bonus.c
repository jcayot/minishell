/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:57:39 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 15:01:39 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list			*new_lst;
	t_list			*new_item;
	void			*data;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst != NULL)
	{
		data = f(lst -> content);
		new_item = ft_lstnew(data);
		if (new_item == NULL)
		{
			del(data);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst = lst -> next;
		ft_lstadd_back(&new_lst, new_item);
	}
	return (new_lst);
}
