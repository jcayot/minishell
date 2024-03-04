/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:20:15 by jcayot            #+#    #+#             */
/*   Updated: 2024/01/31 14:40:53 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memchrother(const void *s, void *current, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
			return ((void *) s + i);
		i++;
	}
	return (current);
}

char	*ft_joinmemstr(void *dst, void const *src, size_t dst_l, size_t src_l)
{
	char	*joined_str;

	joined_str = (char *) malloc((dst_l + src_l + 1) * sizeof (char));
	if (joined_str != NULL)
	{
		ft_memcpy(joined_str, dst, dst_l);
		ft_memcpy(joined_str + dst_l, src, src_l);
		joined_str[dst_l + src_l] = 0;
	}
	free(dst);
	return (joined_str);
}
