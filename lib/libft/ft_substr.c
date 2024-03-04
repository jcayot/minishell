/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:52:52 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/29 17:18:18 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	sub_str_s;

	if (ft_strlen(s) < start)
		sub_str_s = 0;
	else if (len > ft_strlen(s + start))
		sub_str_s = ft_strlen(s + start);
	else
		sub_str_s = len;
	sub_str = malloc((sub_str_s + 1) * sizeof (char));
	if (sub_str == NULL)
		return (NULL);
	i = 0;
	while (start + i < ft_strlen(s) && i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
