/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/29 13:45:52 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef EXIT_SAKU
#  define EXIT_SAKU 1
# endif //EXIT_SAKU

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <libft.h>
# include <get_next_line.h>

typedef struct s_duck
{
	char	*duck_name;
	int		beak_flag;
}	t_duck;

typedef struct s_shell_cmd
{
	t_list	**ins;
	t_list	**outs;
	char	**splitted_command;
	int		error;
}	t_shell_cmd;

typedef struct s_pid_launched
{
	int		n;
	pid_t	*pids;
}	t_pid_launched;

//Environment
t_list			**init_env(char **envp);
int				parse_env(char **split_cmd, t_list *env);
char			*get_env(char *str, t_list *env);
char			**get_envp(t_list *env);

//Parsing
t_shell_cmd		*parse_input(char *input, t_list *env);
void			*free_cmds(t_shell_cmd *cmds);
void			*free_list(t_list **lst, void (*del)(void*));

//Commands
t_pid_launched	run_cmds(t_shell_cmd *cmds, int cmd_n, t_list *env_lst);
int				wait_pids(pid_t *pids, int n);
int				ft_cmdsnum(t_shell_cmd *cmds);

//Utils
void			print_all(t_shell_cmd *commands);
int				sub_strlen(const char *s, char separator);
int				save_inout(int *save_dest);

#endif //MINISHELL_H
