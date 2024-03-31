/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:15 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/20 20:37:18 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int echo(int n, char *args[])
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	if (n > 1 && ft_strncmp(args[1], "-n", 3) == 0)
	{
		nl = 0;
		i++;
	}
	while (i < n)
	{
		if (printf("%s", args[i]) == -1)
			return (EXIT_FAILURE);
		i++;
	}
	if (nl)
		return (printf("\n") != -1);
	return (EXIT_SUCCESS);
}
