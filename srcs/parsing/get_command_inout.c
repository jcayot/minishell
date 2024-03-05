/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_inout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:54:13 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/28 18:54:15 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

t_list	*extract_symbol(char *command_str, char *symbol, t_list *(*item_maker)(char *))
{
	t_list	*item;
	char	*data;
	int		i;
	int		l;

	i = 0;
	i += (int) ft_strlen(symbol);
	while (ft_isspace(command_str[i]))
		i++;
	l = (int) ft_wordlen(command_str + i, ' ');
	if (l == 0)
		return (NULL);
	data = ft_substr(command_str + i, 0, l);
	if (!data)
		return (NULL);
	item = item_maker(data);
	if (!item)
	{
		free(data);
		return (NULL);
	}
	ft_memmove(command_str, command_str + l + i, ft_strlen(command_str + l));
	command_str[l] = 0;
	return (item);
}

t_list	**extract_symbols(char *command_str, char **symbols, t_list *(**item_maker)(char *))
{
	t_list	**extracted;
	t_list	*item;
	int		i;

	extracted = malloc(sizeof (t_list *));
	if (!extracted)
		return (NULL);
	*extracted = NULL;
	while (*command_str)
	{
		i = 0;
		while (symbols[i])
		{
			if (ft_strncmp(command_str, symbols[i], ft_strlen(symbols[i])) == 0)
			{
				item = extract_symbol(command_str, symbols[i], item_maker[i]);
				if (!item)
				{
					ft_lstclear(extracted, &free_inout);
					free(extracted);
					return (NULL);
				}
				ft_lstadd_back(extracted, item);
			}
			i++;
		}
		command_str++;
	}
	return (extracted);
}

int	get_command_inout(t_shell_command *command, char *command_to_parse)
{
	char	*symbols[3];
	t_list	*(*item_makers[3])(char *);

	symbols[0] = "<<";
	symbols[1] = "<";
	item_makers[0] = &make_in_delimiter;
	item_makers[1] = &make_inout_file;
	item_makers[2] = NULL;
	symbols[2] = NULL;
	command -> inputs = extract_symbols(command_to_parse, symbols, item_makers);
	if (!command -> inputs)
		return (0);
	symbols[0] = ">>";
	symbols[1] = ">";
	command -> outputs = extract_symbols(command_to_parse, symbols, item_makers);
	if (!command -> outputs)
	{
		ft_lstclear(command -> inputs, &free_inout);
		free(command -> inputs);
		return (0);
	}
	return (1);
}
