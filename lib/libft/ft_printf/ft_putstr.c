/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 12:25:16 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/20 15:02:37 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str)
{
	int	l;

	if (!str)
		return (ft_putstr("(null)"));
	l = (int) ft_strlen(str);
	if (write(1, str, l) != l)
		return (-1);
	else
		return (l);
}
