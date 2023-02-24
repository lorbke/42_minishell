/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:58:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/25 00:07:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc, exit, size_t
#include <stdio.h> // perror
#include <sys/errno.h> // errno

/* Wrapper function for malloc that checks if allocation size is above zero and
prints an error message and calls exit if allocation failed. */
void	*ft_malloc_safe(size_t size, size_t count)
{
	void	*ptr;

	if (size <= 0 || count <= 0)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
	{
		perror("malloc: ");
		exit(errno);
	}
	return (ptr);
}
