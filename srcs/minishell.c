/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/27 14:24:08 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	minishell(void)
{
	char	*input;

	rl_bind_key('\t', rl_complete);
	using_history();
	while (1)
	{
		input = readline("minishell$> ");
		if (!input)
			break ;
		add_history(input);
		ft_putstr_fd("minishell: command not found: ", 1);
		ft_putendl_fd(input, 1);
		free(input);
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	return (minishell());
}
