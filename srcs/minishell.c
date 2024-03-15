/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/13 18:32:41 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	minishell(void)
{
	pid_t		*pids;
	char		*input;
	t_shell_cmd	*commands;

	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		add_history(input);
		commands = parse_input(input);
		if (commands)
		{
			pids = run_cmds(commands);
			if (pids)
				free(pids);
			free_cmds(commands);
		}
		free(input);
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	return (minishell());
}
