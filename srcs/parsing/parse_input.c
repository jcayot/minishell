/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:56 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/03 17:23:42 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	*free_lst(t_list **lst, void (*del)(void*))
{
	ft_lstclear(lst, del);
	free(lst);
	return (NULL);
}

void	*free_cmds_content(t_shell_cmd *cmds)
{
	int	i;

	i = 0;
	while (!cmds[i].error)
	{
		free_lst(cmds[i].ins, &free_duck);
		free_lst(cmds[i].outs, &free_duck);
		ft_strarray_free(cmds[i].splitted_command);
		cmds[i].ins = NULL;
		cmds[i].outs = NULL;
		cmds[i].splitted_command = NULL;
		i++;
	}
	return (NULL);
}

int broken_pipe(char *str)
{
	int i;
	int pipe;

	i = 0;
	pipe = 0;
	while (str[i])
	{
		if (str[i] == '|')
			pipe = 1;
		else if (!ft_isspace(str[i]))
			pipe = 0;
		i++;
	}
	if (pipe)
		bad_duck(str[i]);
	return (pipe);
}

t_shell_cmd	null_terminate(void)
{
	t_shell_cmd	null;

	null.ins = NULL;
	null.outs = NULL;
	null.splitted_command = NULL;
	null.error = 1;
	return (null);
}

t_shell_cmd	make_cmd(char *cmd_str, t_list *env, int r_val)
{
	char		*env_str;
	t_shell_cmd	cmd;

	cmd = null_terminate();
	env_str = add_env(cmd_str, env, r_val);
	if (!env_str)
		return (cmd);
	if (!get_cmd_inout(&cmd, env_str))
		return (free(env_str), cmd);
	cmd.splitted_command = split_input(env_str, ' ', "\'\"", 1);
	if (!cmd.splitted_command)
	{
		free_lst(cmd.ins, &free_duck);
		free_lst(cmd.outs, &free_duck);
		cmd.ins = NULL;
		cmd.outs = NULL;
		free(env_str);
		return (cmd);
	}
	cmd.error = 0;
	free(env_str);
	return (cmd);
}

t_shell_cmd	*parse_input(char *input, t_list *env, int r_val)
{
	t_shell_cmd	*cmds;
	char		**splitted_input;
	int			n_cmd;
	int			i;

	if (broken_pipe(input))
		return (NULL);
	splitted_input = split_input(input, '|', "\'\"", 0);
	if (!splitted_input)
		return (NULL);
	n_cmd = (int) ft_strarray_len(splitted_input);
	cmds = malloc((n_cmd + 1) * sizeof (t_shell_cmd));
	if (!cmds)
		return (ft_strarray_free(splitted_input));
	i = 0;
	while (i < n_cmd)
	{
		cmds[i] = make_cmd(splitted_input[i], env, r_val);
		if (cmds[i].error != 0)
		{
			ft_strarray_free(splitted_input);
			free_cmds_content(cmds);
			if (cmds[i].error == 1)
				return (free(cmds), NULL);
			return (cmds);
		}
		i++;
	}
	cmds[i] = null_terminate();
	ft_strarray_free(splitted_input);
	return (cmds);
}
