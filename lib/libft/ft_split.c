/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:32:54 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/30 13:23:05 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sub_strlen(const char *s, char separator)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != separator)
		i++;
	return (i);
}

static int	count_word(char const *s, char separator)
{
	int	n;
	int	l;

	n = 0;
	while (*s)
	{
		l = sub_strlen(s, separator);
		if (l != 0)
		{
			n++;
			s += l;
		}
		else
			s++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		n;
	int		i;
	int		l;

	n = count_word(s, c);
	array = (char **) malloc((n + 1) * sizeof (char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		l = sub_strlen(s, c);
		if (l != 0)
		{
			array[i] = ft_substr(s, 0, l);
			if (array[i] == NULL)
				return ((char **) ft_strarray_free(array));
			i++;
		}
		s += (l + 1);
	}
	array[i] = NULL;
	return (array);
}
