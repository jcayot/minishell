/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:10:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 18:10:55 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	if ((oflag & O_CREAT) != 0)
		fd = open(file, oflag, 420);
	else
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
		duck_item = *((t_duck *) (*ducks) -> content);
		might_close(fd);
		if (((t_duck *) (*ducks) -> content) -> beak_flag != O_APPEND)
			fd = open_put_error(duck_item.duck_name, duck_item.beak_flag);
		else
			fd = read_here_doc(((t_duck *) (*ducks) -> content) -> duck_name);
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

pid_t	pipe_and_run(t_shell_cmd cmd, int *in, int out, int last)
{
	int			pipe_fd[2];
	pid_t		pid;
	int 		local_in;
	char 		*cmd_path;

	local_in = *in;
	if (!last)
	{
		pipe(pipe_fd);
		if (out == 1)
			out = pipe_fd[1];
		*in = pipe_fd[0];
	}
	cmd_path = get_path_find_cmd(cmd.splitted_command[0]);
	pid = -1;
	if (cmd_path)
	{
		pid = fork();
		if (pid == 0)
			child_run(local_in, out, cmd_path, cmd.splitted_command);
		free(cmd_path);
	}
	might_close(out);
	might_close(local_in);
	return (pid);
}

pid_t	*run_cmds(t_shell_cmd *cmds)
{
	pid_t	*pids;
	int		i;
	int		in;
	int		out;

	i = 0;
	in = 0;
	pids = malloc(ft_cmdsnum(cmds) * sizeof (int));
	if (!pids)
		return (NULL);
	while (!cmds[i].error)
	{
		out = 1;
		in = open_ducks(cmds[i].inputs, in);
		if (in == -1)
			break ;
		out = open_ducks(cmds[i].outputs, out);
		if (out == -1)
			break ;
		pids[i] = pipe_and_run(cmds[i], &in, out, i == ft_cmdsnum(cmds) - 1);
		i++;
	}
	return (pids);
}
