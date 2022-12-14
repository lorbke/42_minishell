/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:26:56 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/14 15:27:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_stringp(char **stringp, char *start, char *end)
{
	*start = '\0';
	start = *stringp;
	*stringp = end;
	return (start);
}

char	*ft_strsep(char **stringp, const char *delim)
{
	char	*start;
	int		j;

	if (!*stringp || !delim)
		return (NULL);
	start = *stringp;
	if (!**stringp)
	{
		*stringp = NULL;
		return (start);
	}
	while (*start)
	{
		j = 0;
		while (delim[j])
		{
			if (*start == delim[j])
				return (set_stringp(stringp, start, start + 1));
			j++;
		}
		start++;
	}
	if (start != *stringp)
		return (set_stringp(stringp, start, start + 1));
	return (start);
}
