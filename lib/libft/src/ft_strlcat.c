/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:41:39 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/13 18:56:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	destlen;
	size_t	i;

	destlen = ft_strlen(dst);
	i = 0;
	while (src[i] != 0 && destlen + i < dstsize - 1 && dstsize > 0)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	if (destlen > dstsize || dstsize == 0)
		return (ft_strlen(src) + dstsize);
	dst[destlen + i] = 0;
	return (ft_strlen(src) + destlen);
}
