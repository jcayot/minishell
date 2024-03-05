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

t_list	*get_symbol(char *cmd_str, char *symbol, t_list *(*maker)(char *))
{
	t_list	*item;
	char	*data;
	int		i;
	int		l;

	i = 0;
	i += (int) ft_strlen(symbol);
	while (ft_isspace(cmd_str[i]))
		i++;
	l = (int) ft_wordlen(cmd_str + i, ' ');
	if (l == 0)
		return (NULL);
	data = ft_substr(cmd_str + i, 0, l);
	if (!data)
		return (NULL);
	item = maker(data);
	if (!item)
	{
		free(data);
		return (NULL);
	}
	ft_memmove(cmd_str, cmd_str + l + i, ft_strlen(cmd_str + l));
	cmd_str[l] = 0;
	return (item);
}

t_list	**get_symbols(char *cmd_str, char **symbols, t_list *(**maker)(char *))
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
		while (symbols[i])
		{
			if (ft_strncmp(cmd_str, symbols[i], ft_strlen(symbols[i])) == 0)
			{
				item = get_symbol(cmd_str, symbols[i], maker[i]);
				if (!item)
					return (free_list(extracted));
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
	char	*symbols[3];
	t_list	*(*item_makers[3])(char *);

	symbols[0] = "<<";
	symbols[1] = "<";
	item_makers[0] = &make_in_delimiter;
	item_makers[1] = &make_inout_file;
	item_makers[2] = NULL;
	symbols[2] = NULL;
	cmd -> inputs = get_symbols(cmd_str, symbols, item_makers);
	if (!cmd -> inputs)
		return (0);
	symbols[0] = ">>";
	symbols[1] = ">";
	cmd -> outputs = get_symbols(cmd_str, symbols, item_makers);
	if (!cmd -> outputs)
	{
		ft_lstclear(cmd -> inputs, &free_inout);
		free(cmd -> inputs);
		return (0);
	}
	return (1);
}
