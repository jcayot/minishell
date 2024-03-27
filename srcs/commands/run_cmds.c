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

pid_t	run_builtin(t_shell_runnable runnable)
{
	pid_t	result;
	int		save_in;
	int 	save_out;

	save_in = dup(0);
	save_out = dup(1);
	change_fd(runnable.in, 0);
	change_fd(runnable.out, 1);
	result = runnable.builtin(ft_strarray_len(runnable.args), runnable.args);
	change_fd(save_in, 0);
	change_fd(save_out, 1);
	return (result * -1);
}

pid_t	run_child(t_shell_runnable runnable)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (!change_fd(runnable.in, 0))
		{
			close(runnable.out);
			exit(EXIT_FAILURE);
		}
		if (!change_fd(runnable.out, 1))
			exit(EXIT_FAILURE);
		execve(runnable.path, runnable.args, NULL);
		exit(EXIT_FAILURE);
	}
	free(runnable.path);
	return (pid);
}

pid_t	pipe_and_make(t_shell_cmd cmd, int *in, int out, int last)
{
	t_shell_runnable	runnable;
	pid_t				pid;
	int					pipe_fd[2];
	int					local_in;

	local_in = *in;
	if (!last)
	{
		pipe(pipe_fd);
		if (out == 1)
			out = pipe_fd[1];
		*in = pipe_fd[0];
	}
	runnable = make_runnable(cmd.splitted_command, local_in, out);
	pid = -1;
	if (runnable.builtin)
		pid = run_builtin(runnable);
	else if (runnable.path)
		pid = run_child(runnable);
	might_close(out);
	might_close(local_in);
	return (pid);
}

t_pid_launched run_cmds(t_shell_cmd *cmds, int cmd_n)
{
	t_pid_launched	pids_run;
	int				in;
	int				out;

	pids_run.pid_n = 0;
	in = 0;
	pids_run.pids = malloc(ft_cmdsnum(cmds) * sizeof (pid_t));
	if (!pids_run.pids)
		return (pids_run);
	while (pids_run.pid_n < cmd_n)
	{
		out = 1;
		in = open_ducks(cmds[pids_run.pid_n].inputs, in);
		if (in == -1)
			break ;
		out = open_ducks(cmds[pids_run.pid_n].outputs, out);
		if (out == -1)
		{
			might_close(in);
			break ;
		}
		pids_run.pids[pids_run.pid_n] = pipe_and_make(cmds[pids_run.pid_n], &in, out, pids_run.pid_n == cmd_n - 1);
		pids_run.pid_n++;
	}
	return (pids_run);
}
