/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/04 18:17:47 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

typedef struct s_inout
{
	char	*file;
	char	*delimiter;
	int		mode;
}	t_inout;

typedef struct s_shell_command
{
	t_list	**inputs;
	t_list	**outputs;
	char	**splitted_command;
	int		error;
}	t_shell_command;

t_shell_command	*parse_input(char *input);
void			*free_commands(t_shell_command *commands);
void			print_all(t_shell_command *commands);

#endif //MINISHELL_H
