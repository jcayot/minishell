/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:51:44 by svesa             #+#    #+#             */
/*   Updated: 2024/03/16 16:43:39 by svesa            ###   ########.fr       */
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
// static int	check_pipes(char const *s)
// {
// 	int	i;
// 	int	flag;

// 	i = 0;
// 	flag = 0;
// 	printf("%s\n", s);
// 	while(ft_isspace(s[i]))
// 		i++;
// 	if (s[i] == '|')
// 		return (1);
// 	while (s[i])
// 	{
// 		if (s[i] == '|')
// 			flag = 1;
// 		else if (s[i] == '|' && flag == 1 && s[i - 1] != '|')
// 			return (1);
// 		if (!ft_isspace(s[i]))
// 			flag = 0;
// 		i++; 
// 	}
// 	return (0);
// }

char	**ft_modsplit(char const *s, char c)
{
	char	**array;
	int		n;
	int		i;
	int		l;

	// if (check_pipes(s))
	// 	return (bad_duck('|'));
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
