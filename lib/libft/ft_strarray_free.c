/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:17:21 by jcayot            #+#    #+#             */
/*   Updated: 2024/01/31 12:17:25 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strarray_free(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}
