/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:10:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 18:10:55 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int put_file_error(char *file, int error)
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

int open_put_error(char *file, int oflag) //GROS G
{
	int fd;

	fd = open(file, oflag);
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

int open_ducks(t_list **ducks, int fd)
{
	t_duck	duck_item;

	while ((*ducks))
	{
		duck_item = *((t_duck *) (*ducks) -> content);
		if (fd != 0 && fd != 1)
			close(fd);
		if (((t_duck *) (*ducks) -> content) -> beak_flag != O_APPEND)
			fd = open_put_error(duck_item.duck_name, duck_item.beak_flag);
		else
		{
			//GROS G
		}
		if (fd == -1)
			return (-1);
		*ducks = (*ducks) -> next;
	}
	return (fd);
}

int run_cmd(t_shell_cmd cmd, int in, int out)
{
	static int pipe_fd[2];
}

int run_cmds(t_shell_cmd *cmds)
{
	int	i;
	int	in;
	int	out;

	i = 0;
	in = 0;
	while (!cmds[i].error)
	{
		out = 1;
		in = open_ducks(cmds[i].inputs, in);
		if (in == -1)
			return (0);
		out = open_ducks(cmds[i].outputs, out);
		if (out == -1)
			return (close(in) == 1);
		run_cmd(cmds[i], in, out);
		in = out;
		i++;
	}
	return (1);
}
