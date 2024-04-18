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
	if (dst)
		free(dst);
	return (result);
}

char	*simple_quote(char *str, char *env_str, int *i)
{
	char	*result;
	int		j;

	j = 1;
	while (str[*i + j] && str[*i + j] != '\'')
		j++;
	if (str[*i + j])
		j++;
	result = joinsub(env_str, str, *i, j);
	*i += j;
	if (env_str)
		free(env_str);
	return (result);
}

char	*double_quotes(char *str, char *env_str, int *i, int *in_quote)
{
	char	*result;
	int		j;

	j = 1;
	if (str[*i] == '\"')
		*in_quote = !(*in_quote);
	while (str[*i + j] && (*in_quote || str[*i + j] != '\'')
		&& str[*i + j] != '$')
	{
		if (str[*i + j] == '\"')
			*in_quote = !(*in_quote);
		j++;
	}
	result = joinsub(env_str, str, *i, j);
	*i += j;
	if (env_str)
		free(env_str);
	return (result);
}

char	*add_env(char *str, t_list *env, int r_val)
{
	char	*env_str;
	int		i;
	int		in_quote;

	env_str = NULL;
	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && str[i] == '\'')
			env_str = simple_quote(str, env_str, &i);
		else if (str[i] == '$')
		{
			env_str = put_env(env_str, str + i + 1, env, r_val);
			i += var_len(str + i + 1) + 1;
		}
		else
			env_str = double_quotes(str, env_str, &i, &in_quote);
		if (!env_str)
			return (NULL);
	}
	return (env_str);
}
