/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:45:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/12 11:37:59 by fyuzhyk          ###   ########.fr       */
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
	ptr = NULL;
	return (result);
}

char	**realloc_string_array(char **ptr)
{
	char	**result;
	int		i;
	int		len;
	int		ptr_len;

	i = 0;
	ptr_len = 0;
	while (ptr[ptr_len])
		ptr_len++;
	result = malloc(sizeof(char *) * (ptr_len + 2));
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
