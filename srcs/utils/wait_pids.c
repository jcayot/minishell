/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:09:35 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/16 17:09:38 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	wait_pids(pid_t *pids, int n)
{
	int	code;
	int	i;

	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &code, 0);
		i++;
	}
	if (g_signal_not_happy == 130 || g_signal_not_happy == 131)
		return (g_signal_not_happy);
	if (i == 0)
		return (1);
	else if (pids[i - 1] > 0)
		return (WEXITSTATUS(code));
	return (pids[i - 1] * -1);
}
