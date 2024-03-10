/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmakers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:34:59 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 18:29:38 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	*free_list(t_list **extracted)
{
	ft_lstclear(extracted, &free_duck);
	free(extracted);
	return (NULL);
}
