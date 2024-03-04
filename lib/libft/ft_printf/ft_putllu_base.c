/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putllu_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:13:48 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/19 11:46:39 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putllu_base(unsigned long long n, char *base)
{
	int	base_l;
	int	n_l;

	n_l = 0;
	base_l = (int) ft_strlen(base);
	if (n >= (unsigned long long) base_l)
		n_l = ft_putllu_base(n / base_l, base);
	if (n_l < 0 || ft_putchar(base[n % base_l]) != 1)
		return (-1);
	return (n_l + 1);
}
