/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:57:56 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/27 20:00:07 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_parsing.h>

void	*free_lst(t_list **lst, void (*del)(void*))
{
	ft_lstclear(lst, del);
	free(lst);
	return (NULL);
}

void	*free_cmds(t_shell_cmd *cmds)
{
	int	i;

	i = 0;
	while (!cmds[i].error)
	{
		free_lst(cmds[i].ins, &free_duck);
		free_lst(cmds[i].outs, &free_duck);
		ft_strarray_free(cmds[i].splitted_command);
		i++;
	}
	free(cmds);
	return (NULL);
}

t_shell_cmd	make_cmd(char *cmd_str, t_list *env)
{
	t_shell_cmd	cmd;

	cmd.error = 1;
	if (!get_cmd_inout(&cmd, cmd_str))
		return (cmd);
	cmd.splitted_command = ft_modsplit(cmd_str, ' ');
	parse_env(cmd.splitted_command, env);
	if (!cmd.splitted_command)
	{
		free_lst(cmd.ins, &free_duck);
		free_lst(cmd.outs, &free_duck);
		return (cmd);
	}
	cmd.error = 0;
	return (cmd);
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

t_shell_cmd	*parse_input(char *input, t_list *env)
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
	if (!cmds)
		return (ft_strarray_free(cmds_str));
	i = 0;
	while (i < n_cmd)
	{
		cmds[i] = make_cmd(cmds_str[i], env);
		if (cmds[i].error)
		{
			free_cmds(cmds);
			return (ft_strarray_free(cmds_str));
		}
		i++;
	}
	cmds[i] = null_terminate();
	ft_strarray_free(cmds_str);
	return (cmds);
}
