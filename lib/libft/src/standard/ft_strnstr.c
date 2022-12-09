/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:20 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/14 12:05:08 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == 0 || haystack == needle)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] != 0 && i < len)
	{
		j = 0;
		while (haystack[i + j] != 0 && needle[j] != 0
			&& haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == 0)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
