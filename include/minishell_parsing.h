/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:33:20 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/19 12:43:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <minishell.h>

int		get_cmd_inout(t_shell_cmd *cmd, char *cmd_str);
t_list	*make_duck(char *file, char *symbol);
void	free_duck(void *void_duck);
char	**split_input(const char *cmd, char separator, char *exceptions,
			int clean);
char	*cleaned_substr(const char *str, int len, char *to_clean);
int		check_duck_again(char *cmd_str, int *len);
int		broken_pipe(char *str);
int		check_quotes(const char *cmd);

#endif //MINISHELL_PARSING_H
