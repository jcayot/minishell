/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:42:44 by svesa             #+#    #+#             */
/*   Updated: 2024/04/15 18:25:58 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>

static char	*no_match(char *split_cmd, int r_val)
{
	if (split_cmd[1] == '?' && !split_cmd[2])
	{
		free (split_cmd);
		split_cmd = ft_itoa(r_val);
	}
	else
	{
		free(split_cmd);
		split_cmd = malloc(sizeof(char) * 1);
		if (!split_cmd)
			return (NULL);
		split_cmd[0] = '\0';
	}
	return (split_cmd);
}

static char	*make_variable(char *arg, t_list *env, int r_val)
{
	char	*temp;

	temp = get_env(arg, env);
	if (!temp)
		arg = no_match(arg, r_val);
	else
	{
		free(arg);
		arg = malloc(sizeof(char) * ft_strlen(temp) + 1);
		ft_strlcpy(arg, temp, ft_strlen(temp) + 1);
	}
	return (arg);
}

int	parse_env(char **split_cmd, t_list *env, int r_val)
{
	int		i;

	i = 0;
	while (split_cmd[i])
	{
		if (ft_strchr(split_cmd[i], '$'))
		{
			split_cmd[i] = make_variable(split_cmd[i], env, r_val);
			if (!split_cmd[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
