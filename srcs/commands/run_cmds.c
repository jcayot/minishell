/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:10:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/15 18:43:13 by svesa            ###   ########.fr       */
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

pid_t	run(char **splitted_cmd, t_run_context context, int *inout)
{
	t_shell_runnable	run;
	pid_t				pid;
	int					err;

	if (!splitted_cmd[0])
		return (-21);
	run = make_runnable(splitted_cmd, inout, &err, *context.env_lst);
	signals_running();
	if (run.builtin)
		pid = run_builtin(run, context.env_lst, context.cmd_n);
	else if (run.path)
		pid = run_child(run, *context.env_lst, context.inout[0]);
	else
		pid = err * -1;
	return (pid);
}

pid_t	run_loop(t_shell_cmd cmd, t_run_context *context)
{
	pid_t	pid;
	int		local_fd[2];
	int		pipe_fd[2];

	open_inout(cmd.ins, cmd.outs, context -> inout);
	local_fd[0] = context -> inout[0];
	local_fd[1] = context -> inout[1];
	if (context -> cmd_i < context -> cmd_n - 1)
	{
		pipe(pipe_fd);
		if (local_fd[1] == 1)
			local_fd[1] = pipe_fd[1];
		else
			close(pipe_fd[1]);
		context -> inout[0] = pipe_fd[0];
	}
	if (local_fd[0] != -1 && local_fd[1] != -1)
		pid = run(cmd.splitted_command, *context, local_fd);
	else
		pid = 0;
	might_close(local_fd[0]);
	might_close(local_fd[1]);
	return (pid);
}

t_pid_launched	run_cmds(t_shell_cmd *cmds, t_list **env_lst)
{
	t_pid_launched	pids_run;
	t_run_context	context;

	context.inout[0] = 0;
	context.inout[1] = 1;
	context.cmd_n = ft_cmdsnum(cmds);
	context.env_lst = env_lst;
	context.cmd_i = 0;
	pids_run.n = 0;
	pids_run.pids = malloc(context.cmd_n * sizeof (pid_t));
	if (!pids_run.pids)
		return (pids_run);
	while (context.cmd_i < context.cmd_n)
	{
		pids_run.pids[context.cmd_i] = run_loop(cmds[context.cmd_i], &context);
		context.cmd_i++;
	}
	might_close(context.inout[0]);
	pids_run.n = context.cmd_i;
	return (pids_run);
}
