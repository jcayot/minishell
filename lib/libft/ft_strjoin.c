/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:41:15 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 11:05:34 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	str_size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = malloc(str_size);
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, s1, str_size);
	ft_strlcat(joined_str, s2, str_size);
	return (joined_str);
}
