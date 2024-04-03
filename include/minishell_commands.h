/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_commands.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:59 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/03 13:33:47 by svesa            ###   ########.fr       */
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

t_shell_runnable	make_runnable(char **splitted_cmd, int *inout, int *error,
						t_list *env_lst);
int					open_inout(t_list **in_ducks, t_list **out_ducks,
						int *inout);
int					change_fd(int old_fd, int new_fd);
int					might_close(int fd);

//Builtin
int					cd(int n, char *args[], t_list **envp);
int					uitgang(int n, char *args[]);
int					echo(int n, char *args[]);
int					pwd(void);
int					env(int n, char *args[], t_list **envp);
int					export(int n, char *args[], t_list **envp);
int					unset(int n, char *args[], t_list **envp);

#endif //MINISHELL_COMMANDS_H
