/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:32:02 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 13:03:41 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if ((dst > src && dst < src + len))
	{
		i = len;
		while (i != 0)
		{
			i--;
			((char *) dst)[i] = ((char *) src)[i];
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
