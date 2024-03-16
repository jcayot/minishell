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

char	*get_path_find_cmd(char *cmd);
int		open_ducks(t_list **ducks, int fd);
int		change_fd(int old_fd, int new_fd);
int		might_close(int fd);

#endif //MINISHELL_COMMANDS_H
