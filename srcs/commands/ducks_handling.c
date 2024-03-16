/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:52:29 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/16 16:52:30 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

int	put_file_error(char *file, int error)
{
	ft_putstr_fd("-minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	if (error == F_OK)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (error == R_OK)
		ft_putstr_fd("Permission denied\n", 2);
	else if (error == W_OK)
		ft_putstr_fd("Permission denied\n", 2);
	else
		ft_putstr_fd("Unexpected error opening file\n", 2);
	return (-1);
}

int	open_put_error(char *file, int oflag) //GROS G
{
	int	fd;

	fd = open(file, oflag, 420); //PERMISSION ????
	if (fd != -1)
		return (fd);
	if ((oflag & O_RDONLY) != 0)
	{
		if (access(file, F_OK) == -1)
			return (put_file_error(file, F_OK));
		else if (access(file, R_OK) == -1)
			return (put_file_error(file, R_OK));
	}
	if ((oflag & O_WRONLY) != 0)
		return (put_file_error(file, W_OK));
	else
		return (put_file_error(file, INT_MAX));
}

int	read_here_doc(char *delimiter) //DO WITH READLINE PROBABLY
{
	char	*line;
	char	*delimiter_ptr;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	delimiter_ptr = NULL;
	line = get_next_line(0);
	while (line)
	{
		delimiter_ptr = ft_strnstr(line, delimiter, ft_strlen(line));
		if (delimiter_ptr)
			write(pipe_fd[1], line, delimiter_ptr - line);
		else
			write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		if (!delimiter_ptr)
			line = get_next_line(0);
		else
			line = NULL;
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	open_ducks(t_list **ducks, int fd)
{
	t_duck	duck_item;

	while ((*ducks))
	{
		might_close(fd);
		duck_item = *((t_duck *)(*ducks)-> content);
		if (((t_duck *)(*ducks)-> content)-> beak_flag != O_APPEND)
			fd = open_put_error(duck_item.duck_name, duck_item.beak_flag);
		else
			fd = read_here_doc(((t_duck *)(*ducks)-> content)-> duck_name);
		if (fd == -1)
			return (-1);
		*ducks = (*ducks)-> next;
	}
	return (fd);
}
