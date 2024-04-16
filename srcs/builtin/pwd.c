/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:27 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/20 20:37:29 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pwd(void)
{
	char	buffer[10000];

	if (getcwd(buffer, 10000) == NULL)
		return (EXIT_SAKU);
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}
