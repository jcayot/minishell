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

t_shell_cmd	*parse_input(char *input);
void		*free_cmds(t_shell_cmd *cmds);
pid_t *run_cmds(t_shell_cmd *cmds);
void		print_all(t_shell_cmd *commands);
char		*get_path_find_cmd(char *cmd);
int			sub_strlen(const char *s, char separator);
int			ft_cmdsnum(t_shell_cmd *cmds);
int			change_fd(int old_fd, int new_fd);
int			might_close(int fd);

#endif //MINISHELL_H
