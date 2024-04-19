/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:20:19 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/19 18:20:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

int	put_file_error(char *file, char *str_error)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(str_error, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	open_put_error(char *file, int oflag)
{
	int	fd;
	int	error;

	if (oflag == O_RDONLY)
		fd = open(file, oflag);
	else
	{
		if (access(file, F_OK) == 0)
		{
			if (oflag == (O_CREAT | O_WRONLY))
				unlink(file);
		}
		else
			oflag = O_CREAT | O_WRONLY;
		fd = open(file, oflag, 420);
	}
	if (fd != -1)
		return (fd);
	error = errno;
	return (put_file_error(file, strerror(error)));
}
