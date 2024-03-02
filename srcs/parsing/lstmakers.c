//
// Created by Jules Cayot on 3/2/24.
//

#include <minishell_parsing.h>

t_list	*make_in_file(char *file)
{
	t_list	*item;
	t_input	*data;

	data = malloc(sizeof (t_input));
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
	t_input	*data;

	data = malloc(sizeof (t_input));
	if (!data)
		return (NULL);
	data -> file = NULL;
	data -> delimiter = delimiter;
	item = ft_lstnew(data);
	if (!item)
		free(data);
	return (item);
}

t_list	*make_out_file(char *file)
{
	t_list		*item;
	t_output	*data;

	data = malloc(sizeof (t_output));
	if (!data)
		return (NULL);
	data -> file = file;
	item = ft_lstnew(data);
	if (!item)
		free(data);
	return (item);
}

void	free_input(void *data)
{
	t_input	*input;

	input = (t_input *) data;
	if (input -> file)
		free(input -> file);
	if (input -> delimiter)
		free(input -> delimiter);
}

void	free_output(void *data)
{
	t_output	*output;

	output = (t_output *) data;
	if (output -> file)
		free(output -> file);
}
