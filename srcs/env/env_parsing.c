/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:42:44 by svesa             #+#    #+#             */
/*   Updated: 2024/04/04 16:32:24 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>

static char	*no_match(char *split_cmd, int r_val)
{
	free(split_cmd);
	if (split_cmd[1] == '?' && !split_cmd[2])
		split_cmd = ft_itoa(r_val);
	else
	{
		split_cmd = malloc(sizeof(char) * 1);
		split_cmd[0] = '\0';
	}
	return (split_cmd);
}

static int	check_quotes(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

static char	*handle_quotes(char *arg, t_list *env)
{
	char	*temp;

	if (arg[0] == '$')
		return (i_hate_this(arg));
	if (arg[0] == '\'' && arg[ft_strlen(arg) - 1] == '\'')
	{
		arg[ft_strlen(arg) - 1] = '\0';
		temp = get_env(arg + 1, env);
		free(arg);
		arg = malloc(sizeof(char) * ft_strlen(temp) + 3);
		arg[0] = '\'';
		ft_strlcpy(arg + 1, temp, ft_strlen(temp) + 2);
		arg[ft_strlen(temp) + 1] = '\'';
		return (arg);
	}
	if (arg[0] == '"' && arg[ft_strlen(arg) - 1] == '"')
		return (arg);
	if (arg[0] == '"' || arg[0] == '\'')
	{
		free (arg);
		return (bad_duck(arg[0]));
	}
	return (NULL);
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
			if (!check_quotes(split_cmd[i]))
				split_cmd[i] = handle_quotes(split_cmd[i], env);
			else
				split_cmd[i] = make_variable(split_cmd[i], env, r_val);
			if (!split_cmd[i])
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// some chars after env var in bash are written after expanding like /
// also doulbequotes removed unlike bash
// this whole garbo might need rework