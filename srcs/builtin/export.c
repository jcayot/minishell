/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/18 16:13:48 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_commands.h>

static void	export_error(void)
{
	ft_putstr_fd("Nice try. We don't do exact bash copying. ", 2);
	ft_putstr_fd("Try export var=val for proper functionality.\n", 2);
}

static int	parse_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (EXIT_FAILURE);
	while (ft_isalnum(arg[i]) && arg[i])
		i++;
	if (arg[i++] != '=')
		return (EXIT_FAILURE);
	while (ft_isprint(arg[i]) && arg[i])
		i++;
	if (!arg[i])
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}
static	int export_strings(char **args, t_list **envp, int n)
{
	int i;
	int	error_flag;
	
	i = 1;	
	error_flag = 0;
	while (args[i] && i < n)
	{
		if (parse_export(args[i]))
		{
			if (!error_flag)
				export_error();
			error_flag = 1;
		}
		else if (update_env_node(args[i], *envp))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}


int	export(int n, char *args[], t_list **envp)
{
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
	if (export_strings(args, envp, n))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
