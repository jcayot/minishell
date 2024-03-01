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

#include <minishell.h>

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
		else
			i++;
	}
	return (i);
}

t_list	*extract_symbol(char *command_to_parse, int symbol_len)
{
	t_list	*input;
	char	*data;
	int 	i;
	int 	l;

	i = 0;
	while (ft_isspace(command_to_parse[i]))
		i++;
	l = wordlen(command_to_parse, ' ');
	if (l == 0)
		return (NULL);
	data = ft_substr(command_to_parse, 0, l);
	if (!data)
		return (NULL);
	input = ft_lstnew(data);
	if (!input)
		return (free(data), NULL);
	ft_memmove(command_to_parse - symbol_len, command_to_parse + l, ft_strlen(command_to_parse + l));
	return (input);
}

t_list	**get_inputs(char *command_to_parse)
{
	t_list	**inputs;
	t_list	*new_input;
	int 	i;

	inputs = malloc(sizeof (t_list *));
	if (!inputs)
		return (NULL);
	*inputs = NULL;
	i = 0;
	while (command_to_parse[i])
	{
		if (ft_strncmp(command_to_parse, "<<", 2) == 0)
			new_input = extract_symbol(command_to_parse + 2, 2);
		else if (command_to_parse[i] == '<')
			new_input =  extract_symbol(command_to_parse + 1, 1);
		else
		{
			i++;
			continue ;
		}
		if (!new_input)
			return ;//FREE LST
		ft_lstadd_back(inputs, new_input);
	}
	return (inputs);
}

t_list	**get_outputs(char *command_to_parse)
{

}

int	get_command_inout(t_shell_command *command, char *command_to_parse)
{

}
