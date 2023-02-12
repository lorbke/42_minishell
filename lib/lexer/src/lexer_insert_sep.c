/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_insert_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:37:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/12 18:13:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc

size_t	lexer_ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != 0)
		len++;
	return (len);
}

static int	is_special_char(char *str)
{
	if (*str == '<' && *(str + 1) == '<')
		return (2);
	else if (*str == '>' && *(str + 1) == '>')
		return (2);
	else if (*str == '<')
		return (1);
	else if (*str == '>')
		return (1);
	else if (*str == '|' && *(str + 1) == '|')
		return (2);
	else if (*str == '|')
		return (1);
	else if (*str == '&' && *(str + 1) == '&')
		return (2);
	return (0);
}

static int	is_sep_char(char c, char *seps)
{
	while (*seps)
	{
		if (*seps == c)
			return (1);
		seps++;
	}
	return (0);
}

static int	insert_sep_around_special_helper(char **src, char *new, char *seps, int i)
{
	int	offset;

	offset = is_special_char(*src);
	if (offset)
	{
		if (i && !is_sep_char(*(*src - 1), seps))
			new[i++] = ' ';
		while (offset)
		{
			new[i] = **src;
			i++;
			(*src)++;
			offset--;
		}
		if (**src && !is_sep_char(**src, seps))
			new[i++] = ' ';
	}
	else
	{
		new[i++] = **src;
		(*src)++;
	}
	return (i);
}

char	*insert_sep_around_special(char *src, char *seps)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (lexer_ft_strlen(src) + 1000));
	i = 0;
	while (*src)
	{
		i = insert_sep_around_special_helper(&src, new, seps, i);
	}
	new[i] = 0;
	return (new);
}
