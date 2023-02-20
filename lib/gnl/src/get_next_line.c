/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/20 16:18:11 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen
#include "get_next_line.h" // BUFFER_SIZE, get_result

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;
	char		*result;
	int			j;

	j = 0;
	result = malloc(BUFFER_SIZE);
	if (result == NULL)
		return (NULL);
	if (buffer == NULL)
		buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	next_line = get_result(fd, j, buffer, result);
	if (next_line == NULL)
	{
		free(buffer);
		free(result);
		result = NULL;
		buffer = NULL;
	}
	return (next_line);
}
