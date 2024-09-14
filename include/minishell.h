/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/20 14:05:48 by svesa            ###   ########.fr       */
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
# include <signal.h>
# include <termios.h>

extern int					g_signal_not_happy;

typedef struct sigaction	t_sigact;

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
char			*get_env(char *str, t_list *env);
char			**get_envp(t_list *env);

//Parsing
t_shell_cmd		*parse_input(char *input, t_list *env, int r_val);
void			*free_cmds_content(t_shell_cmd *cmds);
void			*free_lst(t_list **lst, void (*del)(void*));
void			*bad_duck(char saku, int special);
char			*add_env(char *str, t_list *env, int r_val);

//Commands
t_pid_launched	run_cmds(t_shell_cmd *cmds, t_list **env_lst, int r_val);
int				wait_pids(pid_t *pids, int n);
int				ft_cmdsnum(t_shell_cmd *cmds);

//Utils
int				sub_strlen(const char *s, char separator);
int				save_inout(int *save_dest);
int				is_not_a_directory(char *path);

//Signals
void			signals_default(void);
void			signals_running(void);
void			signals_hdoc(void);
void			after_input_termios(void);
void			waiting_input_termios(void);

#endif //MINISHELL_H
