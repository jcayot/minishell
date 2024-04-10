/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:51:44 by svesa             #+#    #+#             */
/*   Updated: 2024/04/10 18:55:56 by svesa            ###   ########.fr       */
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

static int	check_pipes(char **s)
{
	int		flag;
	char	*start;

	start = *s;
	flag = 0;
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '|')
		return (1);
	while (**s)
	{
		if (**s == '|' && *(*s + 1) == '|')
			(*s)++;
		else if (**s == '|' && flag == 1)
			return (1);
		else if (**s == '|' || **s == '>' || **s == '<')
			flag = 1;
		else if (!ft_isspace(**s) && **s != '|')
			flag = 0;
		(*s)++;
	}
	*s = start;
	return (0);
}

static int	check_kavychki(char **s)
{
	int		flag;
	char	*start;

	start = *s;
	flag = -1;
	while (ft_isspace(**s))
		(*s)++;
	while (**s)
	{
		if ((**s == 39 || **s == 34) && flag == -1)
			flag = (int)(*s - start);
		else if ((**s == 39 || **s == 34) && flag != -1)
			flag = -1;
		(*s)++;
	}
	if (flag != -1)
	{
		*s = start + flag;
		return (1);
	}
	*s = start;
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
	array[i] = NULL;
	return (0);
}

char	**ft_modsplit(char const *s, char c)
{
	char	**array;
	int		n;

	if (check_pipes((char **)&s) || check_kavychki((char **)&s))
		return (bad_duck((char)*s));
	n = count_word(s, c);
	array = (char **) malloc((n + 1) * sizeof (char *));
	if (array == NULL)
		return (NULL);
	if (make_split(array, s, c, n))
		return ((char **) ft_strarray_free(array));
	return (array);
}
