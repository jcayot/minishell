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
		ft_putstr_fd("-minishell: ", 2);
		perror(runnable.args[0]);
		exit(EXIT_SAKU);
	}
	if (envp)
		ft_strarray_free(envp);
	free(runnable.path);
	return (pid);
}

pid_t	pipe_and_make(t_shell_cmd cmd, t_run_context context)
{
	t_shell_runnable	run;
	pid_t				pid;
	int					pipe_fd[2];
	int					local_fd[2];
	int					err;

	local_fd[0] = context.inout[0];
	local_fd[1] = context.inout[1];
	if (context.cmd_i < context.cmd_n - 1)
	{
		pipe(pipe_fd);
		if (local_fd[1] == 1)
			local_fd[1] = pipe_fd[1];
		context.inout[0] = pipe_fd[0];
	}
	run = make_runnable(cmd.splitted_command, local_fd, &err, *context.env_lst);
	if (run.builtin)
		pid = run_builtin(run, context.env_lst, context.cmd_n);
	else if (run.path)
		pid = run_child(run, *context.env_lst, context.inout[0]);
	else
		pid = err * -1;
	might_close(local_fd[0]);
	might_close(local_fd[1]);
	return (pid);
}

t_pid_launched	run_cmds(t_shell_cmd *cmds, t_list **env_lst)
{
	t_pid_launched	pids_run;
	t_run_context	context;

	context.inout[0] = 0;
	context.cmd_n = ft_cmdsnum(cmds);
	context.env_lst = env_lst;
	context.cmd_i = 0;
	pids_run.n = 0;
	pids_run.pids = malloc(context.cmd_n * sizeof (pid_t));
	if (!pids_run.pids)
		return (pids_run);
	while (context.cmd_i < context.cmd_n)
	{
		if (open_inout(cmds[context.cmd_i].ins, cmds[context.cmd_i].outs, context.inout))
		{
			if (cmds->splitted_command[0])
				pids_run.pids[context.cmd_i] = pipe_and_make(cmds[context.cmd_i], context);
			else
				pids_run.pids[context.cmd_i] = 0;
			might_close(context.inout[1]);
		}
		else
			pids_run.pids[context.cmd_i] = -1;
		context.cmd_i++;
	}
	might_close(context.inout[0]);
	pids_run.n = context.cmd_i;
	return (pids_run);
}
