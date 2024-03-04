/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:07:01 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 13:11:56 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*o;

	if ((unsigned char) c == 0)
		return ((char *) &s[ft_strlen(s)]);
	o = NULL;
	while (*s)
	{
		if (*s == (unsigned char) c)
			o = (char *) s;
		s++;
	}
	return (o);
}
