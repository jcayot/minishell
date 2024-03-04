/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:36:56 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/22 15:32:17 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			dstlen;

	dstlen = ft_strlen(dst);
	if (dstsize == 0 || dstlen > dstsize)
		return (dstsize + ft_strlen(src));
	i = 0;
	while (src[i] && dstsize > dstlen && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = 0;
	return (dstlen + ft_strlen(src));
}
