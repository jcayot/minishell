/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/19 14:13:36 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	commands_handling(t_shell_cmd *commands, t_list **env, int *r_value)
{
	t_pid_launched	pid_launched;

	if (commands)
	{
		if (commands -> splitted_command)
		{
			pid_launched = run_cmds(commands, env);
			if (pid_launched.pids)
			{
				if (*pid_launched.pids != -21)
					*r_value = wait_pids(pid_launched.pids, pid_launched.n);
				free(pid_launched.pids);
			}
		}
		free_cmds_content(commands);
		free(commands);
	}
	else
		*r_value = 258;
}

int	miniloop(t_list **env)
{
	char			*input;
	t_shell_cmd		*commands;
	int				r_value;

	r_value = 0;
	while (1)
	{
		signals_default();
		input = readline("minishell$> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		commands = parse_input(input, *env, r_value);
		commands_handling(commands, env, &r_value);
		free(input);
		after_input_termios();
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
