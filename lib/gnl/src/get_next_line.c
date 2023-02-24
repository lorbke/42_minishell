/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:29:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/24 20:17:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strlen
#include "get_next_line.h" // BUFFER_SIZE, get_result

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;
	char		*result;

	if (fd < 0)
	{
		free(buffer);
		return (NULL);
	}
	result = malloc(BUFFER_SIZE);
	if (result == NULL)
		return (NULL);
	if (buffer == NULL)
		buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (NULL);
	next_line = get_result(fd, 0, buffer, result);
	if (next_line == NULL)
	{
		free(buffer);
		free(result);
		result = NULL;
		buffer = NULL;
	}
	return (next_line);
}
