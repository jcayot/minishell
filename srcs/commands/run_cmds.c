/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:10:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 18:10:55 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

void	child_run(int in, int out, char *cmd_path, char **splitted_cmd)
{
	if (!change_fd(in, 0))
	{
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
	int			local_in;
	char		*cmd_path;

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
