/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_pattern_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:29:57 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:28:06 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen

static int	is_match_valid(char *pattern, char *entry, int *i, int *p_i);
static void	skip_and_set(char *pattern, int *i, char *match);
static void	set_match(char *pattern, int *i, char *match, int *quote_c);
static int	is_outside_quotes(int *i, int *quote_c);

/**
 * It checks if a string matches a pattern
 * 
 * @param entry the string to be matched
 * @param pattern The pattern to match against.
 */
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

/**
 * It checks if the pattern matches the entry
 * 
 * @param pattern The pattern to match against.
 * @param entry the string to be matched
 * @param i the index of the entry string
 * @param p_i pattern index
 * 
 * @return 1 if the pattern matches the entry, 0 otherwise.
 */
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

/**
 * It skips all the stars in the pattern and sets the match 
 * character to the first non-star character in the pattern
 * 
 * @param pattern The pattern to match against.
 * @param i the index of the pattern string
 * @param match the character we're looking for in the string
 */
static void	skip_and_set(char *pattern, int *i, char *match)
{
	while (pattern[*i] == '*' && pattern[*i] != '\0')
		(*i)++;
	if (pattern[*i] != '\0')
		*match = pattern[*i];
}

/**
 * It sets the match character to the next character in the pattern, 
 * skipping over any quotes or
 * wildcards
 * 
 * @param pattern the pattern to match
 * @param i the index of the pattern string
 * @param match the character to match
 * @param quote_c This is the number of quotes that have been encountered.
 */
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

/**
 * It checks if the character is a quote, and if it is, 
 * it changes the value of the quote counter
 * 
 * @param i the index of the current character in the string
 * @param quote_c This is the quote counter. 
 * It's used to keep track of whether or not we're inside of
 * a quote.
 * 
 * @return The value of quote_c.
 */
static int	is_outside_quotes(int *i, int *quote_c)
{
	if (*quote_c == 0)
		*quote_c = 1;
	else
		*quote_c = 0;
	(*i)++;
	return (*quote_c);
}
