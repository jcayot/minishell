/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:37 by svesa             #+#    #+#             */
/*   Updated: 2024/03/28 14:09:52 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_list **env, char **envp)
{
	char	*data;
	int		i;

	i = 0;
	while (envp[i])
	{
		data = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!data)
		{
			if (*env)
				free_list(env, free);
			return (EXIT_FAILURE);
		}
		ft_strlcpy(data, envp[i], ft_strlen(envp[i]) + 1);
		ft_lstadd_back(env, ft_lstnew(data));
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*get_env(char *str, t_list **env)
{
	char	*start;

	start = str;
	while (*env)
	{
		if (!ft_strncmp(str + 1, (*env)->content, ft_strlen(str + 1)))
			return ((char *)((*env)->content) + ft_strlen(start));
		*env = (*env)->next;
	}
	return (NULL);
}

int	parse_env(char **split_cmd, t_list *env)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_cmd[i])
	{
		if (ft_strchr(split_cmd[i], '$'))
		{
			temp = get_env(split_cmd[i], &env);
			free(split_cmd[i]);
			split_cmd[i] = malloc(sizeof(char) * ft_strlen(temp) + 1);
			if (!split_cmd[i])
				return (EXIT_FAILURE);
			ft_strlcpy(split_cmd[i], temp, ft_strlen(temp) + 1);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
