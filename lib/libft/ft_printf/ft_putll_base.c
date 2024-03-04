/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putll_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:32:09 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/20 11:14:15 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putll_base(long long n, char *base)
{
	unsigned long long	abs_n;
	int					l;

	if (n < 0ll)
	{
		if (ft_putchar('-') != 1)
			return (-1);
		if (n == LLONG_MIN)
			abs_n = (unsigned long long)((n + 1ll) * -1ll) + 1ull;
		else
			abs_n = (unsigned long long)(n * -1ll);
	}
	else
		abs_n = n;
	l = ft_putllu_base(abs_n, base);
	if (l < 0)
		return (-1);
	else if (n < 0ll)
		return (l + 1);
	else
		return (l);
}
