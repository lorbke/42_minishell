/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_realloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:45:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 22:42:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_memcpy
#include "../utils.h" // utils_get_str_array_len
#include <string.h> // NULL

char	*utils_ft_realloc(char *ptr, int len)
{
	char	*result;

	result = ft_calloc(sizeof(char), len + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, ptr, len);
	free(ptr);
	ptr = NULL;
	return (result);
}

char	**utils_realloc_str_arr(char **ptr, int size)
{
	char	**result;
	int		i;
	int		len;
	int		ptr_len;

	i = 0;
	ptr_len = utils_get_str_array_len(ptr);
	result = malloc(sizeof(char *) * (ptr_len + size + 1));
	if (result == NULL)
		return (NULL);
	while (ptr[i] != NULL && i < ptr_len)
	{
		len = ft_strlen(ptr[i]);
		result[i] = utils_ft_realloc(ptr[i], len + 1);
		result[i][len] = '\0';
		i++;
	}
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	result[i] = NULL;
	return (result);
}
