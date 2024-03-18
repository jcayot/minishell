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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>
# include <libft.h>
# include <get_next_line.h>

typedef struct s_duck
{
	char	*duck_name;
	int		beak_flag;
}	t_duck;

typedef struct s_shell_cmd
{
	t_list	**inputs;
	t_list	**outputs;
	char	**splitted_command;
	int		error;
}	t_shell_cmd;

typedef struct s_pid_launched
{
	int		pid_n;
	pid_t	*pids;
}	t_pid_launched;

//Parsing
t_shell_cmd	*parse_input(char *input);
void		*free_cmds(t_shell_cmd *cmds);

//Commands
t_pid_launched run_cmds(t_shell_cmd *cmds, int cmd_n);
void		wait_pids(pid_t *pids, int n);
int			ft_cmdsnum(t_shell_cmd *cmds);

//Utils
void		print_all(t_shell_cmd *commands);
int			sub_strlen(const char *s, char separator);

#endif //MINISHELL_H
