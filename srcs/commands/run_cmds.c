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
	int		saved_inout[2];

	if (!save_inout(saved_inout))
		return (-1);
	if (!change_fd(runnable.in, 0))
		return (-1);
	if (!change_fd(runnable.out, 1))
	{
		change_fd(saved_inout[0], 0);
		return (-1);
	}
	result = runnable.builtin(ft_strarray_len(runnable.args), runnable.args);
	change_fd(saved_inout[0], 0);
	change_fd(saved_inout[1], 1);
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
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	free(runnable.path);
	return (pid);
}

pid_t	pipe_and_make(t_shell_cmd cmd, int *inout, int last)
{
	t_shell_runnable	runnable;
	pid_t				pid;
	int					pipe_fd[2];
	int 				local_inout[2];
	int					error;

	local_inout[0] = inout[0];
	local_inout[1] = inout[1];
	if (!last)
	{
		pipe(pipe_fd);
		if (local_inout[1] == 1)
			local_inout[1] = pipe_fd[1];
		inout[0] = pipe_fd[0];
	}
	runnable = make_runnable(cmd.splitted_command, local_inout, &error);
	if (runnable.builtin)
		pid = run_builtin(runnable);
	else if (runnable.path)
		pid = run_child(runnable);
	else
		pid = error * -1;
	might_close(local_inout[0]);
	might_close(local_inout[1]);
	return (pid);
}

t_pid_launched run_cmds(t_shell_cmd *cmds, int cmd_n)
{
	t_pid_launched	pids_run;
	int 			inout[2];

	pids_run.n = 0;
	inout[0] = 0;
	pids_run.pids = malloc(ft_cmdsnum(cmds) * sizeof (pid_t));
	if (!pids_run.pids)
		return (pids_run);
	while (pids_run.n < cmd_n)
	{
		if (open_inout(cmds[pids_run.n].inputs, cmds[pids_run.n].outputs, inout))
			pids_run.pids[pids_run.n] = pipe_and_make(cmds[pids_run.n], inout, pids_run.n == cmd_n - 1);
		else
			pids_run.pids[pids_run.n] = -1;
		pids_run.n++;
	}
	return (pids_run);
}
