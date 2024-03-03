/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:56 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/28 18:54:05 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void *free_commands(t_shell_command *commands)
{
	int	i;

	i = 0;
	while (!commands[i].error)
	{
		ft_lstclear(commands[i].inputs, &free_inout);
		ft_lstclear(commands[i].outputs, &free_inout);
		free(commands[i].inputs);
		free(commands[i].outputs);
		ft_strarray_free(commands[i].splitted_command);
		i++;
	}
	free(commands);
	return (NULL);
}

t_shell_command	make_command(char *command_to_parse)
{
	t_shell_command	command;

	command.error = 1;
	if (!get_command_inout(&command, command_to_parse))
		return (command);
	command.splitted_command = ft_split(command_to_parse, ' ');
	if (!command.splitted_command)
	{
		ft_lstclear(command.inputs, &free_inout);
		ft_lstclear(command.outputs, &free_inout);
		return (command);
	}
	command.error = 0;
	return (command);
}

t_shell_command	*parse_input(char *input)
{
	t_shell_command	*commands;
	char			**commands_to_parse;
	int				commands_number;
	int				i;

	commands_to_parse = ft_split(input, '|');
	if (!commands_to_parse)
		return (NULL);
	commands_number = ft_strarray_len(commands_to_parse);
	commands = malloc((commands_number + 1) * sizeof (t_shell_command));
	i = 0;
	while (commands && i < commands_number)
	{
		commands[i] = make_command(commands_to_parse[i]);
		if (commands[i].error)
		{
			free_commands(commands);
			commands = NULL;
		}
		i++;
	}
	commands[i].error = 1;
	ft_strarray_free(commands_to_parse);
	return (commands);
}
