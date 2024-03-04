/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 22:12:17 by jcayot            #+#    #+#             */
/*   Updated: 2023/10/24 22:12:22 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*s;
	int		l;

	l = (int) ft_intlen(n);
	s = (char *) malloc((l + 1) * sizeof (char));
	if (s == NULL)
		return (NULL);
	s[l] = 0;
	if (n < 0)
		s[0] = '-';
	while (n > 9 || n < -9)
	{
		s[--l] = ft_abs((n % 10)) + '0';
		n /= 10;
	}
	s[--l] = ft_abs((n % 10)) + '0';
	return (s);
}
