/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:33:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/16 16:41:32 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <minishell.h>

int		get_cmd_inout(t_shell_cmd *cmd, char *cmd_str);
t_list	*make_duck(char *file, char *symbol);
void	free_duck(void *void_duck);
void	*free_list(t_list **lst, void (*del)(void*));
char	**ft_modsplit(char const *s, char c);
int		check_duck_again(char *cmd_str, int *len);
void	*bad_duck(char saku);

#endif //MINISHELL_PARSING_H
