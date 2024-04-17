/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:16:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/17 18:16:58 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == ' ' || var[i] == '\"' || var[i] == '\'')
			break ;
		i++;
	}
	return (i);
}

char	*joinsub(char *s1, char *s2, int start, int len)
{
	char	*result;
	char	*sub;

	sub = ft_substr(s2, start, len);
	if (!sub)
		return (NULL);
	result = ft_strjoin(s1, sub);
	free(sub);
	return (result);
}
