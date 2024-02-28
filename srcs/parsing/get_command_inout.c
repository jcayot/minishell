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

t_list	**get_inputs(char *command_to_parse)
{
	t_list	**inputs;
	int 	i;

	inputs = malloc(sizeof (t_list *));
	if (!inputs)
		return (NULL);
	*inputs = NULL;
	while (command_to_parse[i])
	{
		if (ft_strncmp(command_to_parse, "<<", 2) == 0)
		{

		}
		else if (command_to_parse[i] == '<')
		{

		}
		i++;
	}
	return (inputs);
}

t_list	**get_outputs(char *command_to_parse)
{

}

int	get_command_inout(t_shell_command *command, char *command_to_parse)
{

}
