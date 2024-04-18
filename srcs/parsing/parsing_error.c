/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:42:26 by svesa             #+#    #+#             */
/*   Updated: 2024/04/18 14:58:13 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int broken_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	if (str[0])
		pipe = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '|' && pipe == 1)
			return (bad_duck(str[i]), EXIT_FAILURE);
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			pipe = 1;
		else if (!ft_isspace(str[i]) && str[i] != '|')
			pipe = 0;
		i++;
	}
	if (pipe == 1)
		return (bad_duck(str[i]), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

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
//add more escape chars if needed, worked with all ins like bash xept command <>

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
