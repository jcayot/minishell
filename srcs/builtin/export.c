/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:52:55 by svesa             #+#    #+#             */
/*   Updated: 2024/04/03 14:10:58 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	export_error(void)
{
	ft_putstr_fd("Even monkeys know how to use export.\n", 2);
	return (EXIT_FAILURE);
}

static int	parse_export(char *arg) // not exact bash behavior with spaces between inputs or included chars
{
	int	i;

	i = 0;
	while (ft_isalnum(arg[i]) && arg[i])
		i++;
	if (arg[i++] != '=')
		return (EXIT_FAILURE);
	while (ft_isalnum(arg[i]) && arg[i])
		i++;
	if (!arg[i])
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
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
		if (!ft_strncmp(arg, var, len) && var[len] == '=')
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
		free_lst(&envp, free); //we free anyways at the end right?
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
			printf("declare -x %s\n", (char *) (*envp)->content); //kinda bash behavior
			(*envp) = (*envp) -> next;
		}
		*envp = start;
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (args[i] && i < n)
	{
		if (parse_export(args[i]))
			return (export_error());
		do_stuff(args[i], *envp);
		i++;
	}
	return (EXIT_SUCCESS);
}

//might segfault and leak massively (or not)
