/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmakers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:34:59 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/05 16:35:02 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

t_list	*make_inout_file(char *file)
{
	t_list	*item;
	t_inout	*data;

	data = malloc(sizeof (t_inout));
	if (!data)
		return (NULL);
	data -> file = file;
	data -> delimiter = NULL;
	item = ft_lstnew(data);
	if (!item)
		free(data);
	return (item);
}

t_list	*make_in_delimiter(char *delimiter)
{
	t_list	*item;
	t_inout	*data;

	data = malloc(sizeof (t_inout));
	if (!data)
		return (NULL);
	data -> file = NULL;
	data -> delimiter = delimiter;
	item = ft_lstnew(data);
	if (!item)
		free(data);
	return (item);
}

void	free_inout(void *data)
{
	t_inout	*input;

	input = (t_inout *) data;
	if (input -> file)
		free(input -> file);
	if (input -> delimiter)
		free(input -> delimiter);
}
