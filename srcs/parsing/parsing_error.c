/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:42:26 by svesa             #+#    #+#             */
/*   Updated: 2024/03/25 15:59:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_duck_again(char *cmd_str, int *len)
{
	int	i;
	int	flag;

	i = 0;
	while (i < *len)
	{
		if (cmd_str[i] == 39 || cmd_str[i] == 34)
		{
			flag = cmd_str[i++];
			while (i < *len && cmd_str[i] != flag)
				i++;
		}
		if (cmd_str[i] == '<' || cmd_str[i] == '>')
		{
			*len = i;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	escape_chars(char *str, char c)
{
	if (c == '\n' || c == '\0')
	{
		ft_strlcpy(str, "newline", 8);
		return (1);
	}
	else
		return (0);
}
//add more escape chars if needed, worked with all inputs like bash xept command <>

void	*bad_duck(char saku)
{
	char	str[8];

	if (saku == '"' || saku == '\'')
		ft_putstr_fd("minishell: syntax error: open '", 2);
	else
		ft_putstr_fd("minishell: syntax error near token: '", 2);
	if (escape_chars(str, saku))
		ft_putstr_fd(str, 2);
	else
		ft_putchar_fd(saku, 2);
	ft_putchar_fd('\'', 2);
	ft_putendl_fd("", 2);
	return (NULL);
}
