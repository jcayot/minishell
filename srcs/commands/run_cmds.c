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

pid_t grownups_run(char **splitted_command)
{
	if (ft_strncmp(splitted_command[0], "cd", ft_strlen(splitted_command[0])) == 0)
		cd(ft_strarray_len(splitted_command), splitted_command);
	else if (ft_strncmp(splitted_command[0], "exit", ft_strlen(splitted_command[0])) == 0)
		uitgang(ft_strarray_len(splitted_command), splitted_command);
	return (0);
}

pid_t	child_run(int in, int out, char *cmd_path, char **splitted_cmd)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
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
	free(cmd_path);
	return (pid);
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
		if (ft_strncmp(cmd_path, ":builtin:grownups:", ft_strlen(cmd_path)) == 0)
			pid = grownups_run(cmd.splitted_command);
		else
			pid = child_run(local_in, out, cmd_path, cmd.splitted_command);
		free(cmd_path);
	}
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
		pids_run.pids[pids_run.pid_n] = pipe_and_run(cmds[pids_run.pid_n], &in, out, pids_run.pid_n == cmd_n - 1);
		pids_run.pid_n++;
	}
	return (pids_run);
}
