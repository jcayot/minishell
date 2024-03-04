/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:35:47 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/02 16:08:43 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	save_buffer(char *buf_save, ssize_t buf_l)
{
	char	*end;

	if (buf_l > 0)
		end = (char *) ft_memchrother(buf_save, NULL, '\n', buf_l);
	else
		end = NULL;
	if (end && end + 1 < (buf_save + buf_l))
	{
		ft_memcpy(buf_save, end + 1, (buf_l - ((end + 1) - buf_save)));
		buf_save[(buf_l - ((end + 1) - buf_save))] = 0;
	}
	else
		buf_save[0] = 0;
}

static char	*read_line(int fd, char *line, void *buf, ssize_t *read_l)
{
	void	*buf_nl;
	size_t	dst_len;

	buf_nl = NULL;
	dst_len = 0;
	while (*read_l != -1)
	{
		buf_nl = ft_memchrother(buf, buf_nl, '\n', *read_l);
		if (buf_nl != NULL && buf_nl != buf + *read_l)
			line = ft_joinmemstr(line, buf, dst_len, (buf_nl - buf) + 1);
		else if (*read_l > 0)
			line = ft_joinmemstr(line, buf, dst_len, *read_l);
		dst_len += *read_l;
		if ((!line && dst_len != 0) || buf_nl)
			break ;
		*read_l = read(fd, buf, BUFFER_SIZE);
		if (*read_l < BUFFER_SIZE)
			buf_nl = buf + *read_l;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char		buffer_save[BUFFER_SIZE + 1] = "";
	ssize_t			read_l;
	char			*line;

	read_l = (ssize_t) ft_strlen(buffer_save);
	line = NULL;
	line = read_line(fd, line, buffer_save, &read_l);
	if (line && read_l == -1)
	{
		free(line);
		line = NULL;
	}
	save_buffer(buffer_save, read_l);
	return (line);
}
