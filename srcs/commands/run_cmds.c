/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:10:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/03 13:59:07 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

pid_t	run_builtin(t_shell_runnable run, t_list **env)
{
	pid_t	result;
	int		saved_inout[2];

	if (!save_inout(saved_inout))
		return (-1);
	if (!change_fd(run.in, 0))
		return (-1);
	if (!change_fd(run.out, 1))
	{
		change_fd(saved_inout[0], 0);
		return (-1);
	}
	result = run.builtin(ft_strarray_len(run.args), run.args, env);
	change_fd(saved_inout[0], 0);
	change_fd(saved_inout[1], 1);
	return (result * -1);
}

pid_t	run_child(t_shell_runnable runnable, t_list *env, int to_close)
{
	pid_t		pid;
	char		**envp;

	envp = get_envp(env);
	pid = fork();
	if (pid == 0)
	{
		if (!change_fd(runnable.in, 0))
		{
			close(runnable.out);
			exit(EXIT_SAKU);
		}
		if (!change_fd(runnable.out, 1))
			exit(EXIT_SAKU);
		might_close(to_close);
		execve(runnable.path, runnable.args, envp);
		perror("minishell: ");
		exit(EXIT_SAKU);
	}
	if (envp)
		ft_strarray_free(envp);
	free(runnable.path);
	return (pid);
}

pid_t	pipe_and_make(t_shell_cmd cmd, int *inout, int last, t_list **env_lst)
{
	t_shell_runnable	run;
	pid_t				pid;
	int					pipe_fd[2];
	int					local_inout[2];
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
	run = make_runnable(cmd.splitted_command, local_inout, &error, *env_lst);
	if (run.builtin)
		pid = run_builtin(run, env_lst);
	else if (run.path)
		pid = run_child(run, *env_lst, inout[0]);
	else
		pid = error * -1;
	might_close(local_inout[0]);
	might_close(local_inout[1]);
	return (pid);
}

t_pid_launched	run_cmds(t_shell_cmd *cmds, int cmd_n, t_list **env_lst)
{
	t_pid_launched	pids_run;
	int				inout[2];

	pids_run.n = 0;
	inout[0] = 0;
	pids_run.pids = malloc(ft_cmdsnum(cmds) * sizeof (pid_t));
	if (!pids_run.pids)
		return (pids_run);
	while (pids_run.n < cmd_n)
	{
		if (open_inout(cmds[pids_run.n].ins, cmds[pids_run.n].outs, inout))
		{
			if (cmds->splitted_command[0])
				pids_run.pids[pids_run.n] = pipe_and_make(cmds[pids_run.n], inout,pids_run.n == cmd_n - 1, env_lst);
			else
				pids_run.pids[pids_run.n] = 0;
			might_close(inout[1]);
		}
		else
			pids_run.pids[pids_run.n] = -1;
		pids_run.n++;
	}
	might_close(inout[0]);
	return (pids_run);
}
