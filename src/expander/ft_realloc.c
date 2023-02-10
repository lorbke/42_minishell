/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:45:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/10 08:46:25 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_memcpy

char	*ft_realloc(char *ptr, int len)
{
	char	*result;

	result = malloc(sizeof(char) * len);
	if (result == 0)
		return (0);
	ft_memcpy(result, ptr, ft_strlen(ptr));
	free(ptr);
	ptr = 0;
	return (result);
}
