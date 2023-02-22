/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:10:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 17:11:18 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlcpy
#include <stdlib.h> // malloc

char	*ft_strdup_size(char *str, int size)
{
	char	*new_str;

	if (!size)
		return (NULL);
	new_str = malloc(sizeof(char) * size);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, size);
	return (new_str);
}
