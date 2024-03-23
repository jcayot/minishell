/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:51:44 by svesa             #+#    #+#             */
/*   Updated: 2024/03/23 17:11:39 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_parsing.h>

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

static int	check_pipes(char const *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '|')
		return (1);
	while (s[i])
	{
		if (s[i] == '|' && s[i + 1] == '|')
			i++;
		else if (s[i] == '|' && flag == 1)
			return (1);
		else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			flag = 1;
		else if (!ft_isspace(s[i]) && s[i] != '|')
			flag = 0;
		i++;
	}
	return (0);
}

static int	make_split(char **array, char const *s, char c, int n)
{
	int	i;
	int	l;

	i = 0;
	while (i < n)
	{
		l = sub_strlen(s, c);
		if (l != 0)
		{
			if ((*s == '"' || *s == '\'')
				&& (s[l - 1] == '\'' || s[l - 1] == '"'))
				array[i] = ft_substr(s + 1, 0, l - 2);
			else
				array[i] = ft_substr(s, 0, l);
			if (array[i] == NULL)
				return (1);
			i++;
		}
		s += (l + 1);
	}
	return (0);
}
// open quotes are problem, need better solution

char	**ft_modsplit(char const *s, char c)
{
	char	**array;
	int		n;

	if (check_pipes(s))
		return (bad_duck('|'));
	n = count_word(s, c);
	array = (char **) malloc((n + 1) * sizeof (char *));
	if (array == NULL)
		return (NULL);
	if (make_split(array, s, c, n))
		return ((char **) ft_strarray_free(array));
	return (array);
}
