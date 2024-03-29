/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_commands.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:59 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/16 17:26:02 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_COMMANDS_H
# define MINISHELL_COMMANDS_H

# include <minishell.h>

typedef struct s_shell_runnable
{
	int in;
	int out;
	char	*path;
	pid_t	((*builtin)(int, char**));
	char	**args;
}	t_shell_runnable;

t_shell_runnable	make_runnable(char **splitted_cmd, int in, int out);
int					open_ducks(t_list **ducks, int fd);
int					change_fd(int old_fd, int new_fd);
int					might_close(int fd);

//Builtin
int					cd(int n, char *args[]);
int					uitgang(int	n, char *args[]);
int					echo(int n, char *args[]);
int					pwd(void);

#endif //MINISHELL_COMMANDS_H
