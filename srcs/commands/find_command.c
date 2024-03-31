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
	ft_putstr_fd("\n", 2);
	return (NULL);
}

char	*check_access(char *cmd, int *error)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else if (access(cmd, F_OK) == 0)
	{
		*error = 126;
		return (find_error("permission denied: ", cmd));
	}
	else
	{
		*error = 127;
		return (find_error("no such file or directory: ", cmd));
	}
}

char	*find_command(char *cmd, char **paths, int *error)
{
	char	*command_with_path;
	char	*cmd_with_slash;

	if (ft_strncmp(cmd, "./", 2) == 0)
		return (check_access(cmd + 2, error));
	if (ft_strchr(cmd, '/'))
		return (check_access(cmd, error));
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
	*error = 127;
	return (find_error(cmd, ": cmd not found"));
}

void	*find_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (&uitgang);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (&cd);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (&echo);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (&pwd);
	return (NULL);
}

t_shell_runnable make_runnable(char **splitted_cmd, int *inout, int *error, t_list *env_lst)
{
	t_shell_runnable	runnable;
	char				**paths;
	char				*paths_str;

	runnable.in = inout[0];
	runnable.out = inout[1];
	runnable.args = splitted_cmd;
	runnable.path = NULL;
	runnable.builtin = find_builtin(splitted_cmd[0]);
	*error = 1;
	if (runnable.builtin)
		return (runnable);
	paths_str = get_env("PATH", env_lst);
	if (!paths_str)
		return (runnable);
	paths = ft_split(paths_str, ':');
	if (paths)
	{
		runnable.path = find_command(splitted_cmd[0], paths, error);
		ft_strarray_free(paths);
	}
	return (runnable);
}
