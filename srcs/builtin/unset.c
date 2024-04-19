/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:32:40 by svesa             #+#    #+#             */
/*   Updated: 2024/04/19 12:45:05 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_commands.h>

void	check_unset_syntax(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] && !ft_isalpha(arg[0]))
	{
		ft_putstr_fd("Something about identifiers here :", 2);
		ft_putendl_fd(arg, 2);
		return ;
	}
	while (ft_isalnum(arg[i]))
		i++;
	if (arg[i])
	{
		ft_putstr_fd("Something about identifiers here : ", 2);
		ft_putendl_fd(arg, 2);
	}
}

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
		check_unset_syntax(args[i]);
		iterate_list(args[i], envp);
		i++;
	}
	return (EXIT_SUCCESS);
}
