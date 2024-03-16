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

void	wait_pids(pid_t *pids, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}
