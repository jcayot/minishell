/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:40 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/16 18:46:36 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_commands.h>

int	update_env_paths(char *path, t_list **envp)
{
	char	*ptr;
	char	buffer[10000];

	ptr = "OLDPWD=";
	ptr = ft_strjoin(ptr, get_env("PWD", *envp));
	if (!ptr)
		return (EXIT_FAILURE);
	update_env_node(ptr, *envp);
	if (ft_strchr(path, '.'))
	{
		if (getcwd(buffer, 10000) == NULL)
			return (EXIT_FAILURE);
		path = buffer;
	}
	free(ptr);
	ptr = "PWD=";
	ptr = ft_strjoin(ptr, path);
	if (!ptr)
		return (EXIT_FAILURE);
	update_env_node(ptr, *envp);
	free(ptr);
	return (EXIT_SUCCESS);
}

int	go_to_path(char *path, t_list **envp)
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
	if (chdir(path) == -1)
		return (EXIT_FAILURE);
	update_env_paths(path, envp);
	return (EXIT_SUCCESS);
}

int	go_target(t_list **envp, char *target)
{
	char	*target_path;

	target_path = get_env(target, *envp);
	if (!target_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(" not set you retard\n", 2);
		return (EXIT_SAKU);
	}
	else if (ft_strncmp(target, "OLDPWD", 7) == 0)
		ft_putendl_fd(target_path, 1);
	return (go_to_path(target_path, envp));
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

int relative_home(t_list **envp, char *region)
{
	int 	result;
	char	*target_path;
	char 	*el_patho;

	target_path = get_env("HOME", *envp);
	if (!target_path)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(region, 2);
		ft_putstr_fd(" not set you retard\n", 2);
		return (EXIT_SAKU);
	}
	el_patho = ft_strjoin(target_path, region + 1);
	result = go_to_path(el_patho, envp);
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
		return (go_target(envp, "HOME"));
	else
	{
		if (*args[1] == '/')
			return (go_to_path(args[1], envp));
		else if (ft_strncmp(args[1], "-", 2) == 0)
			return (go_target(envp, "OLDPWD"));
		else if (ft_strncmp(args[1], "~", 1) == 0)
			return (relative_home(envp ,args[1]));
		path = get_full_path(args[1]);
		if (!path)
			return (EXIT_SAKU);
		result = go_to_path(path, envp);
		free(path);
		return (result);
	}
}
