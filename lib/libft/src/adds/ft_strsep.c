/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:26:56 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/15 19:56:10 by lorbke           ###   ########.fr       */
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

/* This function tokenizes a string using a set of separators (delimiters) by
replacing the first occurence of a separator char with \0, returning the thereby
created substring and moving the stringp pointer to the next character after
the found separator char. */
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
		return (set_stringp(stringp, start, start));
	return (start);
}
