/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:16:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/19 16:22:04 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>
#include <minishell_commands.h>

int	update_pwd(t_list **env)
{
	char	*pwd;
	char	*path;
	char	buffer[10000];

	if (getcwd(buffer, 10000) == NULL)
		return (EXIT_FAILURE);
	path = buffer;
	pwd = ft_strjoin("PWD=", path);
	if (!pwd)
		return (EXIT_FAILURE);
	if (update_env_node(pwd, *env))
		return (EXIT_FAILURE);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_' || var[i] == '?'))
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

char	*no_match(char *split_cmd, int r_val)
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

char	*make_variable(char *arg, t_list *env, int r_val)
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
