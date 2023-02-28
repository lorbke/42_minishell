/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:58:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:09:04 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_perror_and_exit
#include <stdlib.h> // malloc, exit, size_t

/* Wrapper function for malloc that checks if allocation size is above zero and
prints an error message and calls exit if allocation failed. */
void	*ft_malloc_safe(size_t size, size_t count)
{
	void	*ptr;

	if (size <= 0 || count <= 0)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
		ft_perror_and_exit("malloc: ");
	return (ptr);
}
