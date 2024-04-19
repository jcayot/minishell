/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:07:36 by svesa             #+#    #+#             */
/*   Updated: 2024/04/19 18:27:49 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	r_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_not_happy = 130;
		ft_putchar_fd('\n', 1);
	}
	if (signum == SIGQUIT)
	{
		g_signal_not_happy = 131;
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
	}
}

void	signals_running(void)
{
	t_sigact	sa;

	after_input_termios();
	ft_memset(&sa, 0, sizeof(t_sigact));
	sa.sa_handler = r_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	d_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_not_happy = 1;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_default(void)
{
	t_sigact	sa;

	waiting_input_termios();
	ft_memset(&sa, 0, sizeof(t_sigact));
	sa.sa_handler = d_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
