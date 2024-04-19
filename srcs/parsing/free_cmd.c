/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:03:48 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/18 17:03:50 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	free_duck(void *void_duck)
{
	t_duck	*duck;

	duck = (t_duck *) void_duck;
	if (duck -> duck_name)
		free(duck -> duck_name);
	free(void_duck);
}

void	*free_lst(t_list **lst, void (*del)(void*))
{
	ft_lstclear(lst, del);
	free(lst);
	return (NULL);
}

void	*free_cmds_content(t_shell_cmd *cmds)
{
	int	i;

	i = 0;
	while (!cmds[i].error)
	{
		free_lst(cmds[i].ins, &free_duck);
		free_lst(cmds[i].outs, &free_duck);
		ft_strarray_free(cmds[i].splitted_command);
		cmds[i].ins = NULL;
		cmds[i].outs = NULL;
		cmds[i].splitted_command = NULL;
		i++;
	}
	return (NULL);
}
