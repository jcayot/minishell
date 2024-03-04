/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:41:02 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 14:00:02 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fs;
	size_t			l;
	size_t			i;

	if (s == NULL || f == NULL)
		return (NULL);
	l = ft_strlen(s);
	fs = (char *) malloc((l + 1) * sizeof (char));
	if (fs == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		fs[i] = f((unsigned int) i, s[i]);
		i++;
	}
	fs[i] = 0;
	return (fs);
}
