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

#include <minishell.h>

void	*free_commands(t_shell_command *commands, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_lstclear(commands[i].inputs, &free);
		ft_lstclear(commands[i].outputs, &free);
		free(commands[i].command_path);
		ft_strarray_free(commands[i].splitted_command);
		i++;
	}
	free(commands);
	return (NULL);
}

int get_command_exec(t_shell_command *command, char *command_to_parse)
{

}

t_shell_command	make_command(char *command_to_parse)
{
	t_shell_command	command;

	command.error = 1;
	if (!get_command_inout(&command, command_to_parse))
		return (command);
	if (!get_command_exec(&command, command_to_parse))
	{
		ft_lstclear(command.inputs, &free);
		ft_lstclear(command.outputs, &free);
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
	commands = malloc(commands_number * sizeof (t_shell_command));
	i = 0;
	while (commands && i < commands_number)
	{
		commands[i] = make_command(commands_to_parse[i]);
		if (commands[i].error)
		{
			free_commands(commands, i);
			commands = NULL;
		}
		i++;
	}
	ft_strarray_free(commands_to_parse);
	return (commands);
}
