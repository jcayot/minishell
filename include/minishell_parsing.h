/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:33:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/04 16:01:55 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <minishell.h>

int		get_cmd_inout(t_shell_cmd *cmd, char *cmd_str);
t_list	*make_duck(char *file, char *symbol);
void	free_duck(void *void_duck);
void	*free_lst(t_list **lst, void (*del)(void*));
char	**split_input(char const *s, char c);
int		check_duck_again(char *cmd_str, int *len);
char	*add_env(char *str, t_list *env, int r_val);

#endif //MINISHELL_PARSING_H
