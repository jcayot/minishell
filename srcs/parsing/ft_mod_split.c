/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:51:44 by svesa             #+#    #+#             */
/*   Updated: 2024/03/06 14:54:20 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

static int	sub_strlen(const char *s, char separator)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (s[i] && s[i] != separator)
	{
		if ((s[i] == 39 || s[i] == 34) && !flag)
		{
			flag = s[i];
			i++;
			while (s[i] != flag && s[i])
				i++;
			if (!s[i] || s[i] == separator)
				break ;
		}
		i++;
	}
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

char	**ft_modsplit(char const *s, char c)
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
