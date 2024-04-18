/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:37 by svesa             #+#    #+#             */
/*   Updated: 2024/04/18 16:28:17 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>

t_list	**init_env(char **envp)
{
	t_list	**env_lst;
	char	*data;
	int		i;

	i = 0;
	env_lst = malloc(sizeof (t_list *));
	if (!env_lst)
		return (NULL);
	*env_lst = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "OLDPWD", 6))
			i++;
		data = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!data)
			return (free_lst(env_lst, &free));
		ft_strlcpy(data, envp[i], ft_strlen(envp[i]) + 1);
		ft_lstadd_back(env_lst, ft_lstnew(data));
		i++;
	}
	return (env_lst);
}

char	*get_env(char *str, t_list *env)
{
	char	*start;

	start = str;
	while (env)
	{
		if (str[0] == '$')
		{
			if (!ft_strncmp(str + 1, env->content, ft_strlen(start + 1))
				&& (*((char*)env->content + ft_strlen(start + 1)) == '='))
				return ((char *)(env->content) + ft_strlen(start));
		}
		else if (!ft_strncmp(str, env->content, ft_strlen(start))
			&& (*((char*)env->content + ft_strlen(start)) == '='))
			return ((char *)(env->content) + ft_strlen(start) + 1);
		env = env->next;
	}
	return (NULL);
}

char	**get_envp(t_list *env)
{
	char	**envp;
	int		i;

	envp = malloc((ft_lstsize(env) + 1) * sizeof (char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		envp[i] = ft_strdup(env -> content);
		if (!envp[i])
			return (ft_strarray_free(envp));
		env = env -> next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*i_hate_this(char *arg)
{
	char		*temp;
	static char	set[4] = "$\'\"";

	temp = arg;
	arg = ft_strtrim(arg, set);
	free(temp);
	return (arg);
}
