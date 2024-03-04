/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:57:07 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/19 11:59:38 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr)
{
	int	l;

	l = ft_putstr("0x");
	if (l == -1)
		return (-1);
	return (l + ft_putllu_base((unsigned long long) ptr, "0123456789abcdef"));
}
