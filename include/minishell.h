/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/27 14:24:26 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

typedef struct	s_shell_command
{
	char	*command_path;
	char	*splitted_command;
	char	**env;
}	t_shell_command;

typedef struct	s_shell_input
{
	char 			*input;
	char 			*delimiter;
	char			*output;
	int 			output_mode;
	t_shell_command	*commands;
}	t_shell_input;

#endif //MINISHELL_H
