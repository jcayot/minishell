/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:59:23 by svesa             #+#    #+#             */
/*   Updated: 2024/03/28 13:34:20 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *env)
{
	printf("All stored env vars: \n");
	while (env)
	{
		printf("%s\n", (char *)(env->content));
		env = env->next;
	}
}

void	print_all(t_shell_cmd *commands)
{
	size_t	i;
	size_t	j;
	t_list	**node;
	t_duck	*data;
	
	i = 0;
	j = 0;
	while (!commands[i].error)
	{
		if (i)
			printf("\n");
		printf("Command number: %d\n\n", (int)i);
		node = commands[i].inputs;
		j = 0;
		while (*node)
		{
			printf("Input number : %d\n", (int)j);
			data = (t_duck *)((*node)->content);
			printf("\tFile : %s\n", data->duck_name);
			printf("\tMode : %d\n", data->beak_flag);
			*node = (*node)->next;
			j++;
		}
		node = commands[i].outputs;
		j = 0;
		while (*node)
		{
			printf("Output number : %d\n", (int)j);
			data = (t_duck *)((*node)->content);
			printf("\tFile : %s\n", data->duck_name);
			printf("\tMode : %d\n", data->beak_flag);
			*node = (*node)->next;
			j++;
		}
		j = -1;
		while (commands[i].splitted_command[++j])
			printf("Commands : %s\n", commands[i].splitted_command[j]);
		i++;
	}
}
