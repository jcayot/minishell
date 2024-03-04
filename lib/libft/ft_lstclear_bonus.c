/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:38:46 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 13:44:32 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp_lst;

	if (lst != NULL)
	{
		while (*lst != NULL)
		{
			temp_lst = *lst;
			*lst = (*lst)-> next;
			ft_lstdelone(temp_lst, del);
		}
		lst = NULL;
	}
}
