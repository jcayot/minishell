/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:56 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/06 14:53:43 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	*free_cmds(t_shell_cmd *cmds)
{
	int	i;

	i = 0;
	while (!cmds[i].error)
	{
		ft_lstclear(cmds[i].inputs, &free_inout);
		ft_lstclear(cmds[i].outputs, &free_inout);
		free(cmds[i].inputs);
		free(cmds[i].outputs);
		ft_strarray_free(cmds[i].splitted_command);
		i++;
	}
	free(cmds);
	return (NULL);
}

t_shell_cmd	make_cmd(char *cmd_str)
{
	t_shell_cmd	cmd;

	cmd.error = 1;
	if (!get_cmd_inout(&cmd, cmd_str))
		return (cmd);
	cmd.splitted_command = ft_modsplit(cmd_str, ' ');
	if (!cmd.splitted_command)
	{
		ft_lstclear(cmd.inputs, &free_inout);
		ft_lstclear(cmd.outputs, &free_inout);
		return (cmd);
	}
	cmd.error = 0;
	return (cmd);
}

t_shell_cmd	*parse_input(char *input)
{
	t_shell_cmd	*cmds;
	char		**cmds_str;
	int			n_cmd;
	int			i;

	cmds_str = ft_modsplit(input, '|');
	if (!cmds_str)
		return (NULL);
	n_cmd = (int) ft_strarray_len(cmds_str);
	cmds = malloc((n_cmd + 1) * sizeof (t_shell_cmd));
	i = 0;
	while (cmds && i < n_cmd)
	{
		cmds[i] = make_cmd(cmds_str[i]);
		if (cmds[i].error)
		{
			free_cmds(cmds);
			return (NULL);
		}
		i++;
	}
	cmds[i].error = 1;
	ft_strarray_free(cmds_str);
	return (cmds);
}
