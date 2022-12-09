/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_ftprintf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:48:36 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/09 19:15:08 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	*ft_realloc_ftprintf(void *ptr, size_t size, size_t size_src)
{
	void	*ptr_cpy;

	if (ptr == NULL)
		return (NULL);
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	ptr_cpy = (void *)malloc(size);
	if (ptr_cpy == NULL)
		return (NULL);
	ft_memmove(ptr_cpy, ptr, size_src);
	free(ptr);
	return (ptr_cpy);
}
