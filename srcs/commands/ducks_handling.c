/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ducks_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:52:29 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/17 16:21:35 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_commands.h>

char	*get_env_line(t_list *env, int r_val)
{
	char	*line;
	char	*env_line;

	line = get_next_line(0);
	if (!line)
		return (NULL);
	if (line[ft_strlen(line) - 1] != '\n')
	{
		env_line = add_env(line, env, r_val);
		free(line);
		return (env_line);
	}
	line[ft_strlen(line) - 1] = 0;
	env_line = add_env(line, env, r_val);
	free(line);
	if (!env_line)
		return (NULL);
	line = ft_strjoin(env_line, "\n");
	free(env_line);
	return (line);
}

int	read_coin_coin(char *delimiter, t_list *env, int r_val)
{
	char	*line;
	int		pipe_fd[2];

	signals_hdoc();
	if (pipe(pipe_fd) == -1)
		return (-1);
	line = get_env_line(env, r_val);
	while (line)
	{
		if (ft_strlen(line) - 1 == ft_strlen(delimiter))
		{
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			{
				free(line);
				break ;
			}
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		line = get_env_line(env, r_val);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	open_ducks(t_list *ducks, int fd, t_list *env, int r_val)
{
	t_duck	duck_item;

	while (ducks)
	{
		might_close(fd);
		duck_item = *((t_duck *)ducks-> content);
		if (((t_duck *)ducks-> content)-> beak_flag != O_APPEND)
			fd = open_put_error(duck_item.duck_name, duck_item.beak_flag);
		else
			fd = read_coin_coin(((t_duck *)ducks -> content)->duck_name,
					env, r_val);
		if (fd == -1)
			return (-1);
		ducks = ducks -> next;
	}
	return (fd);
}

int	open_inout(t_list **in_ducks, t_list **out_ducks,
				t_run_context *context, int r)
{
	context->inout[0] = open_ducks(*in_ducks, context->inout[0],
			*context->env_lst, r);
	if (context->inout[0] == -1)
		return (0);
	context->inout[1] = open_ducks(*out_ducks, 1, *context->env_lst, r);
	if (context->inout[1] == -1)
	{
		might_close(context->inout[0]);
		return (0);
	}
	return (1);
}
