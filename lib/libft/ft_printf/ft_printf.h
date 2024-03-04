/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:32:28 by jcayot            #+#    #+#             */
/*   Updated: 2023/11/20 14:40:19 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"

int		ft_printf(const char *format, ...);
int		ft_putllu_base(unsigned long long n, char *base);
int		ft_putll_base(long long n, char *base);
int		ft_putnbr_hexa(unsigned int n);
int		ft_putnbr_hexa_upper(unsigned int n);
int		ft_putunbr(unsigned int n);
int		ft_putnbr(int n);
int		ft_putptr(void *ptr);
int		ft_putstr(char *str);
int		ft_putchar(char c);

#endif //FT_PRINTF_H
