/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:17:06 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:29:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, ft_strlen
#include "../../utils.h" // ft_realloc
#include "../../quotes.h" // find_closing_quote, skip_quotes_in_quotes

/**
 * It takes a string, finds the closing quote, 
 * and returns a string with the contents of the quotes
 * 
 * @param result the string that will be returned
 * @param str the string to be parsed
 * @param i the index of the current character in the string
 * @param result_i the index of the result string
 * 
 * @return A string
 */
char	*handle_quotes(char *result, char *str, int *i, int *result_i)
{
	int		j;
	int		str_len;
	char	*arg;
	char	quote_type;

	quote_type = str[(*i)];
	j = *i;
	str_len = find_closing_quote(str, &(*i), quote_type);
	if (result == NULL)
	{
		arg = malloc(sizeof(char) * str_len + 2);
		if (arg == NULL)
			return (NULL);
	}
	else
		arg = ft_realloc(result, ft_strlen(result) + str_len + 2);
	(*i)++;
	while (j < *i)
	{
		arg[*result_i] = str[j];
		j++;
		(*result_i)++;
	}
	arg[*result_i] = '\0';
	return (arg);
}

/**
 * It finds the closing quote of a string.
 * 
 * @param str The string to be parsed.
 * @param i the index of the string
 * @param quote_type The type of quote that we're looking for.
 * 
 * @return The length of the string.
 */
int	find_closing_quote(char *str, int *i, char quote_type)
{
	int	str_len;

	str_len = 0;
	(*i)++;
	while (str[*i] != '\0')
	{
		str_len++;
		if (str[*i] == quote_type)
			break ;
		(*i)++;
	}
	return (str_len);
}

/**
 * It checks if the next character is a quote, and if it is, 
 * it checks if the number of quotes in the
 * string is odd. If it is, it returns 1, otherwise it returns 0
 * 
 * @param arg The string to be parsed.
 * @param i the index of the current character in the string
 */
int	in_closed_quotes(char *arg, int *i)
{
	int	j;
	int	quote_count;

	j = *i;
	quote_count = 0;
	if (arg[*i + 1] == '"' || arg[*i + 1] == '\'')
	{
		while (arg[j] != '\0')
		{
			if (arg[j] == '"' || arg[j] == '\'')
				quote_count++;
			j++;
		}
		if (quote_count % 2 != 0)
			return (1);
	}
	return (0);
}

/**
 * It copies the contents of a string between two quotes into another string
 * 
 * @param str the string to be parsed
 * @param i the index of the current character in the string
 * @param j the index of the string we're building
 */
void	skip_quotes_in_quotes(char *str, int *i, int *j)
{
	int	quote_type;

	quote_type = str[*i];
	(*i)++;
	while (str[*i] != '\0' && str[*i] != quote_type)
	{
		str[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}
