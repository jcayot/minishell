/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:34:33 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/14 12:34:37 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Special function that might close the integer fd passed as argument
 * if I feel like it.
 * Otherwise, you might still be able to fuck off.
*/

int	might_close(int fd)
{
	if (fd <= 1)
		return (-1);
	return (close(fd));
}

int	change_fd(int old_fd, int new_fd)
{
	int	result;

	result = dup2(old_fd, new_fd);
	might_close(old_fd);
	return (result != -1);
}

int	save_inout(int *save_dest)
{
	save_dest[0] = dup(0);
	if (save_dest[0] == -1)
		return (0);
	save_dest[1] = dup(1);
	if (save_dest[1] == -1)
	{
		close(save_dest[0]);
		return (0);
	}
	return (1);
}
