/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:34:51 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/01 12:29:19 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	length;

	length = ft_strlen(s1) + 1;
	s2 = malloc(length * sizeof (char));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s1, length);
	return (s2);
}
