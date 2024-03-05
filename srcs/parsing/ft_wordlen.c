/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:42:58 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 16:43:07 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

size_t	ft_wordlen(char *str, char end)
{
	size_t	i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			while (str[i] && str[i] != quote)
				i++;
		}
		else if (str[i] == end)
			break ;
		else if (ft_strchr("<>", str[i]))
			return (0);
		else
			i++;
	}
	return (i);
}
