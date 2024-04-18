/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:37 by svesa             #+#    #+#             */
/*   Updated: 2024/04/18 18:05:00 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_env.h>
#include <minishell_commands.h>

static int	make_shell_exec(t_list **env)
{
	char	*ptr;
	char	*another_ptr;

	ptr = ft_strjoin(get_env("PWD", *env), "/minishell");
	if (!ptr)
		return (EXIT_FAILURE);
	another_ptr = ft_strjoin("SHELL=", ptr);
	if (!another_ptr)
	{
		free(ptr);
		return (EXIT_FAILURE);
	}
	free(ptr);
	if (update_env_node(another_ptr, *env))
	{
		free(another_ptr);
		return (EXIT_FAILURE);
	}
	free(another_ptr);
	return (EXIT_SUCCESS);
}

static int	update_shell(t_list **env)
{
	char	*ptr;
	char	*leak;
	int		lvl;

	if (make_shell_exec(env))
		return (EXIT_FAILURE);
	lvl = ft_atoi(get_env("SHLVL", *env)) + 1;
	leak = ft_itoa(lvl);
	ptr = ft_strjoin("SHLVL=", leak);
	free(leak);
	if (!ptr)
		return (EXIT_FAILURE);
	if (update_env_node(ptr, *env))
	{
		free(ptr);
		return (EXIT_FAILURE);
	}
	free(ptr);
	return (EXIT_SUCCESS);
}

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
	update_shell(env_lst);
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
