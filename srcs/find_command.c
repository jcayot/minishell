/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:51:03 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/06 17:47:31 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_error(char *one, char *two)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(one, 2);
	ft_putstr_fd(two, 2);
	ft_putendl_fd("", 2);
	return (NULL);
}

char	*check_access(char *command, int *error)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else if (access(command, F_OK) == 0)
	{
		*error = -126;
		return (find_error("permission denied: ", command));
	}
	else
	{
		*error = 127;
		return (find_error("no such file or directory: ", command));
	}
}

/*
 * Segfault on getenv fail!
 */

char	*find_command(char *command, int *error)
{
	char	*command_with_path;
	char 	**paths;

	paths = ft_split(getenv("PATH"), ':');
	while (paths && *paths)
	{
		command_with_path = ft_strjoin(*paths, command);
		if (!command_with_path)
		{
			*error = -1;
			return (NULL);
		}
		if (access(command_with_path, X_OK) == 0)
			return (command_with_path);
		free(command_with_path);
		paths++;
	}
	if (ft_strncmp(command, "./", 2) == 0)
		return (check_access(command + 2, error));
	if (ft_strchr(command, '/'))
		return (check_access(command, error));
	*error = -127;
	return (find_error(command, ": command not found"));
}
