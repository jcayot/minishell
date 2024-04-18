/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:00:35 by svesa             #+#    #+#             */
/*   Updated: 2024/04/04 16:07:26 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENV_H
# define MINISHELL_ENV_H

# include <minishell.h>

char	*joinsub(char *s1, char *s2, int start, int len);
int		var_len(char *var);
char	*no_match(char *split_cmd, int r_val);
char	*make_variable(char *arg, t_list *env, int r_val);


#endif //MINISHELL_ENV_H