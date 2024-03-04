/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:10:54 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/27 19:10:56 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	slow_strlen(const char *s)
{
	char	*str_iter;

	str_iter = (char *) s;
	while (*str_iter)
		str_iter++;
	return (str_iter - s);
}

static int	align_longword(char **str_move)
{
	while (((unsigned long) *str_move & (sizeof (unsigned long) - 1)) != 0)
	{
		if (!**str_move)
			return (1);
		(*str_move)++;
	}
	return (0);
}

static int	check_bits(unsigned long *long_word, char **str_move)
{
	*str_move = (char *) long_word;
	if (!**str_move)
		return (1);
	if (!*(++*str_move))
		return (1);
	if (!*(++*str_move))
		return (1);
	if (!*(++*str_move))
		return (1);
	if (sizeof (unsigned long) > 4)
	{
		if (!*(++*str_move))
			return (1);
		if (!*(++*str_move))
			return (1);
		if (!*(++*str_move))
			return (1);
		if (!*(++*str_move))
			return (1);
	}
	return (0);
}

static int	make_bits(unsigned long *high_bits, unsigned long *low_bits)
{
	*high_bits = 2155905152;
	*low_bits = 16843009;
	if (sizeof (unsigned long) == 8)
	{
		*high_bits = (*high_bits << 32) | *high_bits;
		*low_bits = (*low_bits << 32) | *low_bits;
		return (1);
	}
	else if (sizeof (unsigned long) == 4)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	unsigned long	*long_word;
	unsigned long	high_bits;
	unsigned long	low_bits;
	char			*str_iter;

	str_iter = (char *) s;
	if (align_longword(&str_iter))
		return (str_iter - s);
	long_word = (unsigned long *) str_iter;
	if (!make_bits(&high_bits, &low_bits))
		return (slow_strlen(str_iter) + (str_iter - s));
	while (1)
	{
		if ((*long_word - low_bits) & high_bits)
		{
			if (check_bits(long_word, &str_iter))
				return (str_iter - s);
		}
		long_word++;
	}
}
