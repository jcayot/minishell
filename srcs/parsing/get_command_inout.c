/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_inout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:54:13 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/28 18:54:15 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	free_duck(void *void_duck)
{
	t_duck	*duck;

	duck = (t_duck *) void_duck;
	if (duck -> duck_name)
		free(duck -> duck_name);
	free(void_duck);
}

t_list	*make_duck(char *file, char *symbol)
{
	t_list	*item;
	t_duck	*data;

	data = malloc(sizeof (t_duck));
	if (!data)
		return (NULL);
	data -> duck_name = file;
	if (ft_strncmp(symbol, "<<", 2) == 0)
		data -> beak_flag = O_APPEND;
	else if (ft_strncmp(symbol, ">>", 2) == 0)
		data -> beak_flag = O_APPEND | O_WRONLY;
	else if (ft_strncmp(symbol, "<", 1) == 0)
		data -> beak_flag = O_RDONLY;
	else if (ft_strncmp(symbol, ">", 1) == 0)
		data -> beak_flag = O_CREAT | O_WRONLY;
	else
	{
		free(data);
		return (NULL);
	}
	item = ft_lstnew(data);
	if (!item)
		free(data);
	return (item);
}

t_list	*get_symbol(char *cmd_str, char *symbol)
{
	t_list	*item;
	char	*data;
	int		i;
	int		l;

	i = (int) ft_strlen(symbol);
	while (ft_isspace(cmd_str[i]))
		i++;
	l = (int) sub_strlen(cmd_str + i, ' ');
	if (l == 0 || check_duck_again(cmd_str + i, &l))
		return (bad_duck(cmd_str[i + l]));
	data = ft_substr(cmd_str + i, 0, l);
	if (!data)
		return (NULL);
	item = make_duck(data, symbol);
	if (!item)
		return (free(data), NULL);
	ft_memmove(cmd_str, cmd_str + l + i, ft_strlen(cmd_str + l + i) + 1);
//	if (l == 1)
//		l += 2;
//	else if (l == 2)
//		l += 1;
	//cmd_str[l] = 0;
	return (item);
}

t_list	**get_symbols(char *cmd_str, char **symbols, int len)
{
	t_list	**extracted;
	t_list	*item;
	int		i;

	extracted = malloc(sizeof (t_list *));
	if (!extracted)
		return (NULL);
	*extracted = NULL;
	while (*cmd_str)
	{
		i = 0;
		while (symbols[i] && i < len)
		{
			if (ft_strncmp(cmd_str, symbols[i], ft_strlen(symbols[i])) == 0)
			{
				item = get_symbol(cmd_str, symbols[i]);
				if (!item)
					return (free_lst(extracted, &free_duck));
				ft_lstadd_back(extracted, item);
			}
			i++;
		}
		cmd_str++;
	}
	return (extracted);
}

int	get_cmd_inout(t_shell_cmd *cmd, char *cmd_str)
{
	char	*symbols[5];

	symbols[0] = "<<";
	symbols[1] = "<";
	symbols[2] = ">>";
	symbols[3] = ">";
	symbols[4] = NULL;
	cmd -> ins = get_symbols(cmd_str, symbols, 2);
	if (!cmd -> ins)
		return (0);
	cmd -> outs = get_symbols(cmd_str, symbols + 2, 2);
	if (!cmd -> outs)
	{
		ft_lstclear(cmd -> ins, &free_duck);
		free(cmd -> ins);
		return (0);
	}
	return (1);
}
