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

	fd = open(file, oflag, 420);
	if (fd != -1)
		return (fd);
	error = errno;
	return (put_file_error(file, strerror(error)));
}

int	read_coin_coin(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];
	int		is_deli;

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = get_next_line(0);
	is_deli = 0;
	while (line)
	{
		write(pipe_fd[1], line, ft_strlen(line));
		if (ft_strlen(line) > 1)
			is_deli = ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0;
		free(line);
		line = NULL;
		if (!is_deli)
			line = get_next_line(0);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	open_ducks(t_list *ducks, int fd)
{
	t_duck	duck_item;

	while (ducks)
	{
		might_close(fd);
		duck_item = *((t_duck *)ducks-> content);
		if (((t_duck *)ducks-> content) -> beak_flag != O_APPEND)
			fd = open_put_error(duck_item.duck_name, duck_item.beak_flag);
		else
			fd = read_coin_coin(((t_duck *)ducks -> content)->duck_name);
		if (fd == -1)
			return (-1);
		ducks = ducks -> next;
	}
	return (fd);
}

int	open_inout(t_list **in_ducks, t_list **out_ducks, int *inout)
{
	inout[0] = open_ducks(*in_ducks, inout[0]);
	if (inout[0] == -1)
		return (0);
	inout[1] = open_ducks(*out_ducks, 1);
	if (inout[1] == -1)
	{
		might_close(inout[0]);
		return (0);
	}
	return (1);
}
