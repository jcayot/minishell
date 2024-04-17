/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/17 14:35:26 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_commands.h>

static int	export_error(void)
{
	ft_putstr_fd("Nice try. We don't do exact bash copying. ", 2);
	ft_putstr_fd("Try export var=val for proper functionality.\n", 2);
	return (EXIT_FAILURE);
}

static int	parse_export(char *args[]) //problems
{
	int	i;
	int	j;

	j = 0;
	while (args[j])
	{
		i = 0;
		while (ft_isalnum(args[j][i]) && args[j][i])
			i++;
		if (args[j][i++] != '=')
			return (EXIT_FAILURE);
		while (ft_isalnum(args[j][i]) && args[j][i])
			i++;
		if (!args[j][i])
			j++;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export(int n, char *args[], t_list **envp)
{
	int		i;
	t_list	*start;

	if (n < 1)
		return (EXIT_FAILURE);
	start = *envp;
	if (n == 1 && !ft_strncmp(args[0], "export", 7))
	{
		while (*envp)
		{
			printf("declare -x %s\n", (char *)(*envp)->content);
			(*envp) = (*envp)->next;
		}
		*envp = start;
		return (EXIT_SUCCESS);
	}
	i = 1;
	if (parse_export(args + 1))
		return (export_error());
	while (args[i] && i < n)
	{
		update_env_node(args[i], *envp);
		i++;
	}
	return (EXIT_SUCCESS);
}
