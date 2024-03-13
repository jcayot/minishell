/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:42:26 by svesa             #+#    #+#             */
/*   Updated: 2024/03/13 18:03:21 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    *bad_duck(char saku)
{
	ft_putstr_fd("minishell: parse error near: '", 2);
	ft_putchar_fd(saku, 2); //CHANGE TO PRINT SYMBOL OF SPECIAL CHAR
	ft_putchar_fd('\'', 2);
	ft_putendl_fd("", 2);
	return (NULL);
}
