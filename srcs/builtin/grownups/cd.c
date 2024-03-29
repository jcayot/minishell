/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:40 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/20 20:37:41 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int go_to_path(char *path)
{
	if (access(path, F_OK) == -1)
		return (printf("cd: %s: No such file or directory. Please make sure that you're not retarded\n", path) != -2);
	else if (access(path, R_OK) == -1)
		return (printf("cd : %s: : Permission denied\n", path) != -2);
	return (chdir(path));
}

int go_home(void)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!home_path)
		return (printf("cd: HOME not set you retard\n") != -2);
	return (go_to_path(home_path));
}

char	*get_full_path(char *relative)
{
	char	buffer[1000];
	char	*path_with_dash;
	char	*full_path;

	if (getcwd(buffer, 1000) == NULL)
		return (NULL);
	path_with_dash = ft_strjoin(buffer, "/");
	if (!path_with_dash)
		return (NULL);
	full_path = ft_strjoin(path_with_dash, relative);
	free(path_with_dash);
	return (full_path);
}

int	cd(int n, char *args[])
{
	int 	result;
	char	*path;

	if (n > 2)
		return (printf("cd: too many arguments\n") != -2);
	else if (n == 1)
		return (go_home());
	else {
		if (*args[1] == '/')
			return (go_to_path(args[1]));
		path = get_full_path(args[1]);
		if (!path)
			return (EXIT_FAILURE);
		result = go_to_path(path);
		free(path);
		return (result);
	}
}
