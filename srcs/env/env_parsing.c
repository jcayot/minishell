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

char	*put_env(char *dst, char *src, t_list *env, int r_val)
{
	char	*result;
	char	*var_name;
	char	*replacement;

	var_name = ft_substr(src, 0, sub_strlen(src, ' '));
	if (!var_name)
		return (NULL);
	printf("%s\n", var_name);
	replacement = make_variable(var_name, env, r_val);
	if (!replacement)
		return (NULL);
	result = ft_strjoin(dst, replacement);
	free(replacement);
	return (result);
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

char	*add_env(char *str, t_list *env, int r_val)
{
	char	*env_str;
	char	*temp_str;
	int		i;
	int		j;

	env_str = NULL;
	i = 0;
	while (str[i])
	{
		j = 1;
		if (str[i] == '\'')
		{
			while (str[i + j] && str[i + j] != '\'')
				j++;
			temp_str = joinsub(env_str, str, i, j);
		}
		else if (str[i] == '$')
		{
			temp_str = put_env(env_str, str + i + 1, env, r_val);
			j = sub_strlen(str + i + j, ' ') + 1;
		}
		else
		{
			while (str[i + j] && str[i + j] != '\'' && str[i + j] != '$')
				j++;
			temp_str = joinsub(env_str, str, i, j);
		}
		if (env_str)
			free(env_str);
		if (!temp_str)
			return (NULL);
		env_str = temp_str;
		i += j;
	}
	printf("%s\n", env_str);
	return (env_str);
}
