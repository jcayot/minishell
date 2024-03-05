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

int run_cmd(t_shell_cmd cmd, int in, int out)
{

}

int run_cmds(t_shell_cmd *cmds)
{
	int i;

	i= 0;
	while (!cmds[i].error)
	{
		run_cmd(cmds[i]);
		i++;
	}
	return (1);
}
