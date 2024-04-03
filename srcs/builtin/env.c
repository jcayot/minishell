/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:53:44 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/03 14:54:43 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env(int n, char *args[], t_list **envp)
{
	t_list	*start;

	if (n != 1 || !args)
		return (EXIT_SAKU);
	start = *envp;
	while (*envp)
	{
		printf("%s\n", (char *)(*envp)->content);
		(*envp) = (*envp)->next;
	}
	*envp = start;
	return (EXIT_SUCCESS);
}
