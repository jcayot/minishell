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
		might_close(fd);
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


void	child_run(int in, int out, char *cmd_path, char **splitted_cmd)
{
	if (!change_fd(in, 0)) {
		close(out);
		exit(EXIT_FAILURE);
	}
	if (!change_fd(out, 1))
		exit(EXIT_FAILURE);
	execve(cmd_path, splitted_cmd, NULL);
	exit(EXIT_FAILURE);
}

int pipe_and_run(t_shell_cmd cmd, int *in, int out)
{
	int			pipe_fd[2];
	pid_t		pid;
	int 		local_in;
	char 		*cmd_path;

	local_in = *in;
	pipe(pipe_fd);
	if (out == 1)
		out = pipe_fd[1];
	*in = pipe_fd[0];
	cmd_path = find_command(cmd.splitted_command[0]);
	pid = fork();
	if (pid == 0)
		child_run(local_in, out);
	free(cmd_path);
	might_close(pipe_fd[1]);
	might_close(local_in);
	return (pid);
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
		pipe_and_run(cmds[i], &in, out);
		i++;
	}
	might_close(in);
	return (1);
}
