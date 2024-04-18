/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_commands.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:59 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/17 14:37:21 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMANDS_H
# define MINISHELL_COMMANDS_H

# include <minishell.h>

typedef struct s_shell_runnable
{
	int		in;
	int		out;
	char	*path;
	pid_t	((*builtin)(int32_t, char **, t_list **));
	char	**args;
}	t_shell_runnable;

typedef struct s_run_context
{
	t_list	**env_lst;
	int		inout[2];
	int		cmd_i;
	int		cmd_n;
}	t_run_context;

t_shell_runnable	make_runnable(char **splitted_cmd, int *inout, int *error,
						t_list *env_lst);
int					open_inout(t_list **in_ducks, t_list **out_ducks,
						int *inout);
int					change_fd(int old_fd, int new_fd);
int					might_close(int fd);
pid_t				run_builtin(t_shell_runnable run, t_list **env_lst,
						int cmd_n);

//Builtin
int					cd(int n, char *args[], t_list **envp);
int					uitgang(int n, char *args[]);
int					echo(int n, char *args[]);
int					pwd(void);
int					env(int n, char *args[], t_list **envp);
int					export(int n, char *args[], t_list **envp);
int					unset(int n, char *args[], t_list **envp);

//Utils
int					update_env_node(char *arg, t_list *envp);
int					update_env_paths(char *path, t_list **envp);
t_list				*check_duplicate_nodes(char *arg, t_list *envp);

#endif //MINISHELL_COMMANDS_H
