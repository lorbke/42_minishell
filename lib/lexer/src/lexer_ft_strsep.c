/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ft_strsep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:26:56 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/08 18:48:12 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_private.h" // main header
#include <stdlib.h> // for NULL

static char	*lexer_ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (c == 0)
		return (&((char *)s)[i]);
	return (NULL);
}

static char	*set_stringp(char **stringp, char *start, char *end)
{
	*start = '\0';
	start = *stringp;
	*stringp = end;
	return (start);
}

static char	*ignore_delims(char *stringp, const char *ignore)
{
	char	*esc;
	char	*start;

	start = stringp;
	esc = lexer_ft_strchr(ignore, *start);
	if (esc && *esc == '(')
		esc++;
	if (esc)
	{
		start++;
		while (*start && *start != *esc)
			start++;
		if (!*start)
			return (set_stringp(&stringp, start, start));
	}
	return (start);
}

// @todo unclosed quote handling

/* For the minishell project, the function had to be modified because
quote-handling with the original one would have been overly complicated.
Now, a third parameter specifies a set of chars, that when encountered will cause
the function to ignore delims until that specific char is encountered again.*/

/* This function tokenizes a string using a set of delimiters by
replacing the first occurence of a delim char with \0, returning the thereby
created substring and moving the stringp pointer to the next character after
the found delim char. */
char	*lexer_ft_strsep(char **stringp, const char *delim, const char *ignore)
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
		start = ignore_delims(start, ignore);
		j = 0;
		while (delim[j])
		{
			if (*start == delim[j++])
				return (set_stringp(stringp, start, start + 1));
		}
		start++;
	}
	if (start != *stringp)
		return (set_stringp(stringp, start, start));
	return (start);
}
