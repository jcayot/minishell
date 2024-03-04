/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:18:23 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/06 11:14:30 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	total = count * size;
	if (total / size != count)
		return (NULL);
	ptr = (void *) malloc(total);
	if (ptr != NULL)
		ft_bzero(ptr, total);
	return (ptr);
}
