/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:31:09 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/21 10:21:52 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_argument(const char *format, va_list *args)
{
	if (*format == 'c')
		return (ft_putchar((char) va_arg(*args, int)));
	else if (*format == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (*format == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (*format == 'd')
		return (ft_putnbr(va_arg(*args, int)));
	else if (*format == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (*format == 'u')
		return (ft_putunbr(va_arg(*args, unsigned int)));
	else if (*format == 'x')
		return (ft_putnbr_hexa(va_arg(*args, unsigned int)));
	else if (*format == 'X')
		return (ft_putnbr_hexa_upper(va_arg(*args, unsigned int)));
	else if (*format == '%')
		return (ft_putchar('%'));
	else
		return (ft_putchar(*format));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		len_add;

	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			len_add = print_argument((++format), &args);
		else
			len_add = ft_putchar(*format);
		if (len_add < 0)
		{
			len = -1;
			break ;
		}
		len += len_add;
		format++;
	}
	va_end(args);
	return (len);
}
