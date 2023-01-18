/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:52:18 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/23 19:23:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	allocsize;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	allocsize = count * size;
	ptr = (size_t *)malloc(allocsize);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, allocsize);
	return (ptr);
}
