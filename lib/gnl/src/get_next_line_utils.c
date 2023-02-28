/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 09:56:33 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 22:42:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../src/utils.h" // utils_ft_realloc
#include "libft.h" // ft_strlen, ft_memcpy
#include "get_next_line.h" // BUFFER_SIZE

char	*get_result(int fd, int j, char *buffer, char *result)
{
	static int	i;
	static int	control;

	if (control <= i)
	{
		control = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	}
	if (control <= 0)
		return (NULL);
	while (buffer[i] != '\n' && i < control && control != 0)
	{
		result[j++] = buffer[i++];
		if (control == i)
		{
			result = utils_ft_realloc(result, j + BUFFER_SIZE);
			control = read(fd, buffer, BUFFER_SIZE);
			i = 0;
		}
	}
	if (buffer[i++] == '\n' && control != 0)
		result[j++] = '\n';
	result[j] = '\0';
	return (result);
}
