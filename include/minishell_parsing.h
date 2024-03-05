/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:33:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 18:21:28 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <minishell.h>

int		get_cmd_inout(t_shell_cmd *cmd, char *cmd_str);
t_list	*make_inout_file(char *file);
t_list	*make_in_delimiter(char *delimiter);
void	free_inout(void *data);
size_t	ft_wordlen(char *str, char end);
void	*free_list(t_list **extracted);

#endif //MINISHELL_PARSING_H