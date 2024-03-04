/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:36:57 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/02 14:49:19 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif //BUFFER_SIZE

char	*get_next_line(int fd);
void	*ft_memchrother(const void *s, void *current, int c, size_t n);
char	*ft_joinmemstr(void *dst, void const *src, size_t dst_l, size_t src_l);

#endif //GET_NEXT_LINE_H
