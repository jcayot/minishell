/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:33:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 16:33:23 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <minishell.h>

int		get_command_inout(t_shell_command *command, char *command_to_parse);
t_list	*make_inout_file(char *file);
t_list	*make_in_delimiter(char *delimiter);
void	free_inout(void *data);
size_t	ft_wordlen(char *str, char end);

#endif //MINISHELL_PARSING_H
