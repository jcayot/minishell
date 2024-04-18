/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:42:44 by svesa             #+#    #+#             */
/*   Updated: 2024/04/17 19:31:23 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>

static char	*no_match(char *split_cmd, int r_val)
{
	if (split_cmd[0] == '?' && !split_cmd[1])
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

char	*put_env(char *dst, char *src, t_list *env, int r_val)
{
	char	*result;
	char	*var_name;
	char	*replacement;

	var_name = ft_substr(src, 0, var_len(src));
	if (!var_name)
		return (NULL);
	replacement = make_variable(var_name, env, r_val);
	if (!replacement)
		return (NULL);
	result = ft_strjoin(dst, replacement);
	free(replacement);
	return (result);
}

char	*add_env(char *str, t_list *env, int r_val)
{
	char	*env_str;
	char	*temp_str;
	int		in_quote;
	int		i;
	int		j;

	env_str = NULL;
	i = 0;
	in_quote = 0;
	while (str[i])
	{
		j = 1;
		if (!in_quote && str[i] == '\'')
		{
			while (str[i + j] && str[i + j] != '\'')
				j++;
			if (str[i + j])
				j++;
			temp_str = joinsub(env_str, str, i, j);
		}
		else if (str[i] == '$')
		{
			temp_str = put_env(env_str, str + i + 1, env, r_val);
			j = var_len(str + i + j) + 1;
		}
		else
		{
			if (str[i] == '\"')
				in_quote = !in_quote;
			while (str[i + j] && (in_quote || str[i + j] != '\'') && str[i + j] != '$') {
				if (str[i + j] == '\"')
					in_quote = !in_quote;
				j++;
			}
			temp_str = joinsub(env_str, str, i, j);
		}
		if (env_str)
			free(env_str);
		if (!temp_str)
			return (NULL);
		env_str = temp_str;
		i += j;
	}
	return (env_str);
}
