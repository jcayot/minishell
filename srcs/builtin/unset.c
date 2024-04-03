/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:32:40 by svesa             #+#    #+#             */
/*   Updated: 2024/04/03 14:40:25 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_list	*check_dups(char *arg, t_list *envp)
{
	char	*var;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
    while (envp)
	{
        var = envp -> content;
        if (!ft_strncmp(arg, var, len) && var[len] == '=')
            return (envp);
		envp = envp -> next;
	}
	return (NULL);
}
void  iterate_macac(char *arg, t_list **envp)
{
    t_list  *node;
    t_list  *start;
    
	start = *envp;
    node = check_dups(arg, start);
    if (!node)
        return ; //bash seems to not care if var doesnt exist
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

int unset(int n, char **args, t_list **envp)
{
    int     i;
    
    if (n < 1)
        return (EXIT_FAILURE);
    i = 1;
    while (args[i])
    {
        iterate_macac(args[i], envp);
        i++;
    }
    return (EXIT_SUCCESS);
}
