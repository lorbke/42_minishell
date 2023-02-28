/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:29:57 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 13:51:18 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen

static int	is_match_valid(char *pattern, char *entry, int *i, int *p_i);
static void	skip_and_set(char *pattern, int *i, char *match);
static void	set_match(char *pattern, int *i, char *match, int *quote_c);
static int	is_outside_quotes(int *i, int *quote_c);

int	is_match(char *entry, char *pattern)
{
	int		i;
	int		p_i;
	int		quote_c;
	char	match;

	i = 0;
	p_i = 0;
	quote_c = 0;
	match = 0;
	set_match(pattern, &p_i, &match, &quote_c);
	while (entry[i] != '\0')
	{
		if (p_i == 0 && entry[i] != pattern[p_i])
			break ;
		while (entry[i] != '\0' && entry[i] != match)
			i++;
		if (entry[i] == match && is_match_valid(pattern, entry, &i, &p_i) == 0)
			break ;
		set_match(pattern, &p_i, &match, &quote_c);
	}
	if (pattern[p_i] == '\0' && entry[i] == '\0')
		if (pattern[ft_strlen(pattern) - 1] == '*' || entry[i - 1] == match)
			return (1);
	return (0);
}

static int	is_match_valid(char *pattern, char *entry, int *i, int *p_i)
{
	if (*p_i != 0 && pattern[*p_i] != '\0')
	{
		if (pattern[*p_i - 1] != '*')
		{
			if (pattern[*p_i - 1] == entry[*i - 1] || pattern[*p_i] == '*')
				(*p_i)++;
			else
				return (0);
		}
		else
			(*p_i)++;
	}
	else if (pattern[*p_i] != '\0')
		(*p_i)++;
	(*i)++;
	return (1);
}

static void	skip_and_set(char *pattern, int *i, char *match)
{
	while (pattern[*i] == '*' && pattern[*i] != '\0')
		(*i)++;
	if (pattern[*i] != '\0')
		*match = pattern[*i];
}

static void	set_match(char *pattern, int *i, char *match, int *quote_c)
{
	if (pattern[*i] == '\'')
	{
		if (is_outside_quotes(&(*i), &(*quote_c)))
			*match = pattern[*i];
		else
			skip_and_set(pattern, &(*i), &(*match));
	}
	else if (pattern[*i] != '*' && pattern[*i] != '\0')
		*match = pattern[*i];
	else
		skip_and_set(pattern, &(*i), &(*match));
}

static int	is_outside_quotes(int *i, int *quote_c)
{
	if (*quote_c == 0)
		*quote_c = 1;
	else
		*quote_c = 0;
	(*i)++;
	return (*quote_c);
}
