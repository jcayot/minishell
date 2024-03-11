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

#include <minishell.h>

int	sub_strlen(const char *s, char separator)
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
