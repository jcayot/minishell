/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:32:40 by svesa             #+#    #+#             */
/*   Updated: 2024/04/17 14:35:25 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_commands.h>

static void	iterate_list(char *arg, t_list **envp)
{
	t_list	*node;
	t_list	*start;

	start = *envp;
	node = check_duplicate_nodes(arg, start);
	if (!node)
		return ;
	while (*envp)
	{
		if (node == (*envp)->next || node == start)
			break ;
		*envp = (*envp)->next;
	}
	if (node == start)
	{
		start = start->next;
		*envp = start;
	}
	else
		(*envp)->next = (*envp)->next->next;
	ft_lstdelone(node, &free);
	*envp = start;
}

int	unset(int n, char **args, t_list **envp)
{
	int	i;

	if (n < 1)
		return (EXIT_FAILURE);
	i = 1;
	while (args[i])
	{
		iterate_list(args[i], envp);
		i++;
	}
	return (EXIT_SUCCESS);
}
