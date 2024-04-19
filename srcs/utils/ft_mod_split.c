/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:51:44 by svesa             #+#    #+#             */
/*   Updated: 2024/04/19 12:42:57 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell_parsing.h>

int	word_len(const char *cmd, char separator, char *exceptions)
{
	int		len;

	len = 0;
	while (cmd[len])
	{
		if (cmd[len] == separator)
			break ;
		if (ft_strchr(exceptions, cmd[len]))
		{
			if (!ft_strchr(cmd + len + 1, cmd[len]))
				return (-1);
			len += (int)(ft_strchr(cmd + len + 1, cmd[len]) - (cmd + len));
		}
		len++;
	}
	return (len);
}

int	count_words(const char *cmd, char separator, char *exceptions)
{
	int	n;
	int	w_len;

	n = 0;
	if (check_quotes(cmd))
		return (-42);
	while (*cmd)
	{
		w_len = word_len(cmd, separator, exceptions);
		if (w_len == -1)
			return (-1);
		else if (w_len > 0)
		{
			n++;
			cmd += w_len;
		}
		else
			cmd++;
	}
	return (n);
}

char	*cleaned_substr(const char *str, int len, char *to_clean)
{
	char	*cleaned;
	char	cleaning;
	int		i;
	int		j;

	cleaned = malloc((ft_strlen(str) + 1) * sizeof (char));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strchr(to_clean, str[i]))
		{
			cleaning = str[i++];
			while (i < len && str[i] != cleaning)
				cleaned[j++] = str[i++];
		}
		else
			cleaned[j++] = str[i++];
	}
	cleaned[j] = 0;
	return (cleaned);
}

char	*get_split(const char *cmd, int len, char *exceptions, int clean)
{
	if (clean)
		return (cleaned_substr(cmd, len, exceptions));
	else
		return (ft_substr(cmd, 0, len));
}

char	**split_input(const char *cmd, char separator,
						char *exceptions, int clean)
{
	char	**splitted_cmd;
	int		n_word;
	int		i;
	int		len;

	n_word = count_words(cmd, separator, exceptions);
	if (n_word == -1 || n_word == -42)
		return (bad_duck(cmd[ft_strlen(cmd)], n_word));
	splitted_cmd = malloc((n_word + 1) * sizeof (char *));
	if (!splitted_cmd)
		return (NULL);
	i = 0;
	while (i < n_word)
	{
		len = word_len(cmd, separator, exceptions);
		if (len != 0)
		{
			splitted_cmd[i] = get_split(cmd, len, exceptions, clean);
			if (!splitted_cmd[i++])
				return (ft_strarray_free(splitted_cmd));
		}
		cmd += (len + 1);
	}
	splitted_cmd[i] = NULL;
	return (splitted_cmd);
}
