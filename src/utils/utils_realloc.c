/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:45:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 17:28:29 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_memcpy
#include "../utils.h" // get_string_array_len

char	*ft_realloc(char *ptr, int len)
{
	char	*result;

	result = malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, ptr, len - 1);
	free(ptr);
	ptr = NULL;
	return (result);
}

char	**realloc_string_array(char **ptr, int size)
{
	char	**result;
	int		i;
	int		len;
	int		ptr_len;

	i = 0;
	ptr_len = get_string_array_len(ptr);
	result = malloc(sizeof(char *) * (ptr_len + size + 1));
	if (result == NULL)
		return (NULL);
	while (ptr[i] != NULL && i < ptr_len)
	{
		len = ft_strlen(ptr[i]);
		result[i] = ft_realloc(ptr[i], len + 1);
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
