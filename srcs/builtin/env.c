/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:53:44 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/01 15:53:46 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env(int n, char *args[], t_list *envp)
{
	if (n != 1 || !args)
		return (EXIT_SAKU);
	while (envp)
	{
		printf("%s\n", (char *) envp -> content);
		envp = envp -> next;
	}
	return (EXIT_SUCCESS);
}
