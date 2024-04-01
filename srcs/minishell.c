/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/27 20:51:20 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	miniloop(t_list **env)
{
	t_pid_launched	pid_launched;
	char			*input;
	t_shell_cmd		*commands;
	int				r_value;

	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		add_history(input);
		commands = parse_input(input, *env);
		free(input);
		if (commands)
		{
			pid_launched = run_cmds(commands, ft_cmdsnum(commands), *env);
			if (pid_launched.pids)
			{
				r_value = wait_pids(pid_launched.pids, pid_launched.n);
				printf("%d\n", r_value);
				free(pid_launched.pids);
			}
			free_cmds(commands);
		}
	}
	return (EXIT_SUCCESS);
}

int	minishell(char **envp)
{
	t_list			**env;

	rl_bind_key('\t', rl_complete);
	using_history();
	env = init_env(envp);
	miniloop(env);
	free_lst(env, &free);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 && argv && envp)
		return (minishell(envp));
	else
		return (EXIT_SAKU);
}
