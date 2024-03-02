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

size_t	wordlen(char *str, char separator)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			while (str[i] && str[i] != quote)
				i++;
			quote = 0;
		}
		else if (str[i] == separator)
			break ;
		else if (ft_strchr("<>", str[i]))
			return (0);
		else
			i++;
	}
	return (i);
}

t_list	*extract_symbol(char *command_to_parse, char *symbol, t_list *(*item_maker)(char *))
{
	t_list	*item;
	char	*data;
	int 	i;
	int 	l;

	i = 0;
	i += ft_strlen(symbol);
	while (ft_isspace(command_to_parse[i]))
		i++;
	l = wordlen(command_to_parse + i, ' ');
	if (l == 0)
		return (NULL);
	data = ft_substr(command_to_parse + i, 0, l);
	if (!data)
		return (NULL);
	item = item_maker(data);
	if (!item)
	{
		free(data);
		return (NULL);
	}
	ft_memmove(command_to_parse, command_to_parse + l, ft_strlen(command_to_parse + l));
	command_to_parse[l] = 0;
	return (item);
}

t_list	**extract_symbols(char *command_to_parse, char **symbols, t_list  *(*item_maker[2]) (char *), void (*del)(void*))
{
	t_list	**extracted;
	t_list	*item;
	int 	i;

	extracted = malloc(sizeof (t_list *));
	*extracted = NULL;
	while (*command_to_parse)
	{
		i = 0;
		while (i < 2)
		{
			if (ft_strncmp(command_to_parse, symbols[i], ft_strlen(symbols[i])) == 0)
			{
				item = extract_symbol(command_to_parse, symbols[i], item_maker[i]);
				if (!item)
				{
					ft_lstclear(extracted, del);
					return (NULL);
				}
				ft_lstadd_back(extracted, item);
			}
			i++;
		}
	}
	return (extracted);
}

int	get_command_inout(t_shell_command *command, char *command_to_parse)
{
	char	*symbols[3];
	t_list	*(*item_makers[3]) (char *);

	symbols[0] = "<<";
	symbols[1] = "<";
	item_makers[0] = &make_in_delimiter;
	item_makers[1] = &make_in_file;
	item_makers[2] = NULL;
	symbols[2] = NULL;
	command -> inputs = extract_symbols(command_to_parse, symbols, item_makers, &free_input);
	if (!command -> inputs)
		return (0);
	symbols[0] = ">>";
	symbols[1] = ">";
	item_makers[0] = &make_out_file;
	item_makers[1] = NULL;
	command -> outputs = extract_symbols(command_to_parse, symbols, item_makers, &free_output);
	if (!command -> outputs)
	{
		ft_lstclear(command -> inputs, &free_input);
		return (0);
	}
	return (1);
}
