/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:37 by svesa             #+#    #+#             */
/*   Updated: 2024/03/29 13:42:52 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		data = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!data)
			return (free_list(env_lst, &free));
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
			if (!ft_strncmp(str + 1, env->content, ft_strlen(start + 1)))
				return ((char *)(env->content) + ft_strlen(start));
		}
		else if (!ft_strncmp(str, env->content, ft_strlen(start)))
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

int	parse_env(char **split_cmd, t_list *env)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_cmd[i])
	{
		if (ft_strchr(split_cmd[i], '$'))
		{
			temp = get_env(split_cmd[i], env);
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
