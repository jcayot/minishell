/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/02 10:32:23 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_export(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isprint(args[i][j]) && args[i][j] != 32) //not bash behavior
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

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
		if (!ft_strncmp(arg, var, len))
			return (envp);
		envp = envp -> next;
	}
	return (NULL);
}

static int	do_stuff(char *arg, t_list *envp)
{
	char	*data;
	t_list	*asd;

	data = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (!data)
	{
		free_lst(&envp, free);
		return (EXIT_FAILURE);
	}
	ft_strlcpy(data, arg, ft_strlen(arg) + 1);
	if (check_dups(arg, envp))
	{
		asd = check_dups(arg, envp);
		free(asd->content);
		asd->content = data;
	}
	else
		ft_lstadd_back(&envp, ft_lstnew(data));
	return (EXIT_SUCCESS);
}

int	export(int n, char *args[], t_list *envp)
{
	int	i;

	if (parse_export(args + 1))
		return (EXIT_FAILURE);
	if (n == 1 && !ft_strncmp(args[0], "export", 7))
	{
		while (envp)
		{
			printf("declare -x %s\n", (char *) envp->content); //kinda bash behavior
			envp = envp -> next;
		}
		return (EXIT_SUCCESS);
	}
	i = 1;
	if (n > 1)
	{
		while (args[i] && i < n)
		{
			do_stuff(args[i], envp);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

//might segfault and leak massively (or not)
