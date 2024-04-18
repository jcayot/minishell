/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uitgang.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:37:51 by jcayot            #+#    #+#             */
/*   Updated: 2024/03/20 20:37:53 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exit_error(char *str)
{
	ft_putstr_fd("exit : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

static unsigned char	retardedtoi(char *str)
{
	char	*str_save;
	long	n;
	long	haunting_past;
	char	minus;

	str_save = str;
	n = 0;
	haunting_past = 0;
	minus = 0;
	if (*str == '-' || *str == '+')
		minus = *(str++);
	if (*str >= '0' && *str <= '9')
		n = (*(str++) - '0');
	if (minus == '-')
		n *= -1;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*(str++) - '0');
		if ((n > 0 && n < haunting_past) || (n < 0 && n > haunting_past))
			return (exit_error(str_save));
		haunting_past = n;
	}
	if (*str != 0)
		return (exit_error(str_save));
	return ((unsigned char) n);
}

int	uitgang(int n, char *args[])
{
	ft_putstr_fd("exit\n", 2);
	if (n == 1)
		exit(EXIT_SUCCESS);
	exit(retardedtoi(args[1]));
}
