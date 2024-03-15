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

char	*check_access(char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else if (access(command, F_OK) == 0)
		return (find_error("permission denied: ", command));
	else
		return (find_error("no such file or directory: ", command));
}

char *find_command(char *command, char **paths)
{
	char	*command_with_path;
	char	*cmd_with_slash;

	while (paths && *paths)
	{
		cmd_with_slash = ft_strjoin("/", command);
		if (!cmd_with_slash)
			return (NULL);
		command_with_path = ft_strjoin(*paths, cmd_with_slash);
		free(cmd_with_slash);
		if (!command_with_path)
			return  (NULL);
		if (access(command_with_path, X_OK) == 0)
			return (command_with_path);
		free(command_with_path);
		paths++;
	}
	if (ft_strncmp(command, "./", 2) == 0)
		return (check_access(command + 2));
	if (ft_strchr(command, '/'))
		return (check_access(command));
	return (find_error(command, ": command not found"));
}

char	*get_path_find_cmd(char *cmd)
{
	char	**paths;
	char	*paths_str;
	char	*cmd_with_path;

	paths_str = getenv("PATH");
	if (!paths_str)
		return (NULL);
	cmd_with_path = NULL;
	paths = ft_split(paths_str, ':');
	if (paths)
		cmd_with_path = find_command(cmd, paths);
	return (cmd_with_path);
}
