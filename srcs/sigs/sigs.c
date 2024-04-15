/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:07:36 by svesa             #+#    #+#             */
/*   Updated: 2024/04/15 18:46:46 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	r_handler(int signum)
{
	if (signum == SIGINT)
 		ft_putchar_fd('\n', 1);
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
	}
}

void    signals_running(void)
{
	t_sigact	sa;

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
		write(1, "minishell$>   ", 14);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void    signals_default(void)
{
	t_sigact	sa;

	ft_memset(&sa, 0, sizeof(t_sigact));
	sa.sa_handler = d_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
