/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:56 by jcayot            #+#    #+#             */
/*   Updated: 2024/04/17 20:01:37 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

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

t_shell_cmd	*make_cmds(char **splitted_in, int n_cmd, t_list *env, int r_val)
{
	t_shell_cmd	*cmds;
	int			i;

	cmds = malloc((n_cmd + 1) * sizeof (t_shell_cmd));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < n_cmd)
	{
		cmds[i] = make_cmd(splitted_in[i], env, r_val);
		if (cmds[i].error != 0)
		{
			free_cmds_content(cmds);
			free(cmds);
			return (NULL);
		}
		i++;
	}
	cmds[i] = null_terminate();
	return (cmds);
}

t_shell_cmd	*parse_input(char *input, t_list *env, int r_val)
{
	t_shell_cmd	*cmds;
	char		**splitted_input;
	int			n_cmd;

	if (broken_pipe(input))
		return (NULL);
	splitted_input = split_input(input, '|', "\'\"", 0);
	if (!splitted_input)
		return (NULL);
	n_cmd = (int) ft_strarray_len(splitted_input);
	cmds = make_cmds(splitted_input, n_cmd, env, r_val);
	ft_strarray_free(splitted_input);
	return (cmds);
}
