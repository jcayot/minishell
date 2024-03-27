/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:51:03 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/16 13:07:02 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

char	*find_error(char *one, char *two)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(one, 2);
	ft_putstr_fd(two, 2);
	ft_putendl_fd("", 2);
	return (NULL);
}

char	*check_access(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK) == 0)
		return (find_error("permission denied: ", cmd));
	else
		return (find_error("no such file or directory: ", cmd));
}

char	*find_command(char *cmd, char **paths)
{
	char	*command_with_path;
	char	*cmd_with_slash;

	while (paths && *paths)
	{
		cmd_with_slash = ft_strjoin("/", cmd);
		if (!cmd_with_slash)
			return (NULL);
		command_with_path = ft_strjoin(*paths, cmd_with_slash);
		free(cmd_with_slash);
		if (!command_with_path)
			return (NULL);
		if (access(command_with_path, X_OK) == 0)
			return (command_with_path);
		free(command_with_path);
		paths++;
	}
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (check_access(cmd + 2));
	if (ft_strchr(cmd, '/'))
		return (check_access(cmd));
	return (find_error(cmd, ": cmd not found"));
}

//TODO Might require to replace : by some character forbidden in files/folder names
char	*find_builtin(char *cmd)
{
	const char	babies[2][10] = {"echo", "pwd"};
	const char	grownups[2][10] = {"cd", "uitgang"};
	int i;

	i = 0;
	while (i < 2)
	{
		if (ft_strncmp(cmd, babies[i], ft_strlen(cmd)) == 0)
			return (ft_strjoin(":builtin:babies:", cmd));
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (ft_strncmp(cmd, grownups[i], ft_strlen(cmd)) == 0)
			return (ft_strjoin(":builtin:grownups", cmd));
		i++;
	}
	return (NULL);
}

char	*get_path_find_cmd(char *cmd)
{
	char	**paths;
	char	*paths_str;
	char	*cmd_with_path;

	if (ft_strncmp(cmd, "", 1) == 0)
		return (NULL);
	cmd_with_path = find_builtin(cmd);
	if (cmd_with_path)
		return (cmd_with_path);
	paths_str = getenv("PATH");
	if (!paths_str)
		return (NULL);
	cmd_with_path = NULL;
	paths = ft_split(paths_str, ':');
	if (paths)
	{
		cmd_with_path = find_command(cmd, paths);
		ft_strarray_free(paths);
	}
	return (cmd_with_path);
}
