/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:43:14 by jcayot            #+#    #+#             */
/*   Updated: 2024/02/15 13:01:31 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	n;
	int		m;

	n = 0;
	m = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		m = *str++;
	if (!ft_isdigit(*str))
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + *(str++) - '0';
		if (m == '-' && n > ((long) INT_MIN) * -1l)
			return (0);
		else if (m != '-' && n > (long) INT_MAX)
			return (-1);
	}
	if (m == '-')
		n *= -1;
	return ((int) n);
}
