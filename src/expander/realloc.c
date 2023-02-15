/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:45:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 18:13:30 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_memcpy

char	*ft_realloc(char *ptr, int len)
{
	char	*result;

	result = malloc(sizeof(char) * len);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, ptr, len);
	free(ptr);
	return (result);
}

char	**realloc_string_array(char **ptr, int size)
{
	char	**result;
	int		i;
	int		len;
	int		ptr_len;

	i = 0;
	ptr_len = 0;
	while (ptr[ptr_len] != NULL)
		ptr_len++;
	result = malloc(sizeof(char *) * (ptr_len + size) + 1);
	while (ptr[i] != NULL)
	{
		len = ft_strlen(ptr[i]);
		result[i] = ft_realloc(ptr[i], len + 1);
		result[i][len] = '\0';
		i++;
	}
	free(ptr);
	result[i] = NULL;
	return (result);
}
