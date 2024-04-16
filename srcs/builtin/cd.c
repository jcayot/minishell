/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:40 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/03 12:38:55 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	go_to_path(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : No such file or directory."
			" Please make sure that you're not retarded\n", 2);
		return (EXIT_SAKU);
	}
	else if (access(path, R_OK) == -1)
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		return (EXIT_SAKU);
	}
	return (chdir(path));
}

int	go_target(t_list *envp, char *target)
{
	char	*target_path;

	target_path = get_env(target, envp);
	if (!target_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(" not set you retard\n", 2);
		return (EXIT_SAKU);
	}
	else if (ft_strncmp(target, "OLDPWD", 7) == 0)
		ft_putendl_fd(target_path, 1);
	return (go_to_path(target_path));
}

char	*get_full_path(char *relative)
{
	char	buffer[10000];
	char	*path_with_dash;
	char	*full_path;

	if (getcwd(buffer, 10000) == NULL)
		return (NULL);
	if (buffer[ft_strlen(buffer) - 1] != '/')
		path_with_dash = ft_strjoin(buffer, "/");
	else
		path_with_dash = ft_strdup(buffer);
	if (!path_with_dash)
		return (NULL);
	full_path = ft_strjoin(path_with_dash, relative);
	free(path_with_dash);
	return (full_path);
}

int relative_home(t_list *envp, char *region)
{
	int 	result;
	char	*target_path;
	char 	*el_patho;

	target_path = get_env("HOME", envp);
	if (!target_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(region, 2);
		ft_putstr_fd(" not set you retard\n", 2);
		return (EXIT_SAKU);
	}
	el_patho = ft_strjoin(target_path, region + 1);
	result = go_to_path(el_patho);
	free(el_patho);
	return (result);
}

int	cd(int n, char *args[], t_list **envp)
{
	int		result;
	char	*path;

	if (n > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_SAKU);
	}
	else if (n == 1)
		return (go_target(*envp, "HOME"));
	else
	{
		if (*args[1] == '/')
			return (go_to_path(args[1]));
		else if (ft_strncmp(args[1], "-", 2) == 0)
			return (go_target(*envp, "OLDPWD"));
		else if (ft_strncmp(args[1], "~", 1) == 0)
			return (relative_home(*envp ,args[1]));
		path = get_full_path(args[1]);
		if (!path)
			return (EXIT_SAKU);
		result = go_to_path(path);
		free(path);
		return (result);
	}
}
