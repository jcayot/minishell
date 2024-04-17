/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:11:35 by svesa             #+#    #+#             */
/*   Updated: 2024/04/17 18:11:49 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

pid_t	builtin(t_shell_runnable run, t_list **env_lst)
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
	result = run.builtin(ft_strarray_len(run.args), run.args, env_lst);
	change_fd(saved_inout[0], 0);
	change_fd(saved_inout[1], 1);
	return (result);
}

pid_t	run_builtin(t_shell_runnable run, t_list **env_lst, int cmd_n)
{
	pid_t	result;

	if (cmd_n > 1)
	{
		result = fork();
		if (result == 0)
			exit(builtin(run, env_lst));
		return (result);
	}
	else
		return (builtin(run, env_lst) * -1);
}
