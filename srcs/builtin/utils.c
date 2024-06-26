/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:24:24 by svesa             #+#    #+#             */
/*   Updated: 2024/04/20 14:06:07 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

t_list	*check_duplicate_nodes(char *arg, t_list *envp)
{
	char	*var;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (envp)
	{
		var = envp -> content;
		if (!ft_strncmp(arg, var, len) && var[len] == '=')
			return (envp);
		envp = envp -> next;
	}
	return (NULL);
}

static int	update_oldpwd(t_list **envp)
{
	char	*ptr;

	if (!get_env("OLDPWD", *envp))
		return (EXIT_SUCCESS);
	ptr = ft_strjoin("OLDPWD=", get_env("PWD", *envp));
	if (!ptr)
		return (EXIT_FAILURE);
	if (update_env_node(ptr, *envp))
		return (free(ptr), EXIT_FAILURE);
	free(ptr);
	return (EXIT_SUCCESS);
}

int	update_env_paths(char *path, t_list **envp)
{
	char	*ptr;
	char	buffer[10000];

	if (update_oldpwd(envp))
		return (EXIT_FAILURE);
	if (!get_env("PWD", *envp))
		return (EXIT_SUCCESS);
	if (ft_strchr(path, '.'))
	{
		if (getcwd(buffer, 10000) == NULL)
			return (EXIT_FAILURE);
		path = buffer;
	}
	ptr = ft_strjoin("PWD=", path);
	if (!ptr)
		return (EXIT_FAILURE);
	if (update_env_node(ptr, *envp))
		return (free(ptr), EXIT_FAILURE);
	free(ptr);
	return (EXIT_SUCCESS);
}

int	update_env_node(char *arg, t_list *envp)
{
	char	*data;
	t_list	*asd;

	data = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (!data)
		return (EXIT_FAILURE);
	ft_strlcpy(data, arg, ft_strlen(arg) + 1);
	if (check_duplicate_nodes(arg, envp))
	{
		asd = check_duplicate_nodes(arg, envp);
		free(asd->content);
		asd->content = data;
	}
	else
		ft_lstadd_back(&envp, ft_lstnew(data));
	return (EXIT_SUCCESS);
}

int	is_not_a_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}
