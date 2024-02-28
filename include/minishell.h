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

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

typedef struct	s_input
{
	char	*file;
	char	*delimiter;
}	t_input;

typedef struct	s_output
{
	char	*file;
	int		mode;
}	t_output;

typedef struct	s_shell_command
{
	t_list	**inputs;
	t_list	**outputs;
	char	*command_path;
	char	**splitted_command;
	int 	error;
}	t_shell_command;

int	get_command_inout(t_shell_command *command, char *command_to_parse);

#endif //MINISHELL_H
