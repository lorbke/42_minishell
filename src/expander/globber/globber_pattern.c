/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:27:50 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen
#include "globber_private.h" // create_new_path
#include "../../utils.h" // realloc_string_array, get_string_array_len

static void	scan_char(char **arg, char **pattern, int *astrsk_c, int *quote_c);
static void	set_char(char **arg, char **pattern, int *astrsk_c, int *quote_c);
static void	set_literal_astrsk(char **pattern);

/**
 * It scans the string and copies it to a new string, 
 * while replacing the '*' character with '.*' and
 * the '?' character with '.'
 * 
 * @param arg the argument to be scanned
 * @param i the number of characters in the pattern
 * 
 * @return a pointer to the first character of the pattern.
 */
char	*find_pattern(char *arg, int *i)
{
	char	*tmp;
	char	*pattern;
	int		j;
	int		quote_c;
	int		astrsk_c;

	pattern = malloc(sizeof(char) * ft_strlen(arg) + 10);
	if (pattern == NULL)
		return (NULL);
	tmp = pattern;
	quote_c = 0;
	astrsk_c = 0;
	j = 0;
	while (*arg != '\0')
	{
		scan_char(&arg, &pattern, &astrsk_c, &quote_c);
		j++;
	}
	*i = j - 1;
	*pattern = '\0';
	pattern = tmp;
	return (pattern);
}

/**
 * It takes a string array, a string, and a string, and returns a string array
 * 
 * @param result The array of strings that will be returned.
 * @param entry the name of the file/directory
 * @param path The path to the directory we're currently in.
 * 
 * @return A string array of all the files in the directory.
 */
char	**pattern_over(char **result, char *entry, char *path)
{
	int	i;

	i = 0;
	if (result != NULL)
	{
		i = get_string_array_len(result);
		result = realloc_string_array(result, 2);
	}
	else
	{
		result = malloc(sizeof(char *) * 2);
		if (result == NULL)
			return (NULL);
	}
	result[i] = create_new_path(path, entry);
	result[i + 1] = NULL;
	return (result);
}

/**
 * It takes a string and converts it into a pattern string
 * 
 * @param arg The argument string.
 * @param pattern the address of the pointer to the pattern string
 * @param astrsk_c This is a counter for the number of asterisks in a row.
 * @param quote_c This is a counter for the number of quotes.
 */
static void	set_char(char **arg, char **pattern, int *astrsk_c, int *quote_c)
{
	if (**arg == '*' && *astrsk_c == 0)
	{
		if (*quote_c == 0)
		{
			*astrsk_c = 1;
			**pattern = **arg;
		}
		else
			set_literal_astrsk(&(*pattern));
		(*pattern)++;
	}
	else
	{
		if (**arg != '*')
		{
			*astrsk_c = 0;
			**pattern = **arg;
			(*pattern)++;
		}
	}
	(*arg)++;
}

/**
 * It scans the input string for characters and sets the pattern 
 * string accordingly
 * 
 * @param arg the string to be scanned
 * @param pattern the pattern to be matched
 * @param astrsk_c This is a counter for the number of asterisks in a row.
 * @param quote_c This is a flag that indicates whether 
 * we are in a quoted string or not.
 */
static void	scan_char(char **arg, char **pattern, int *astrsk_c, int *quote_c)
{
	if (**arg == '\'' || **arg == '\"')
	{
		if (*quote_c == 0)
			*quote_c = 1;
		else
			*quote_c = 0;
		*astrsk_c = 0;
		(*arg)++;
	}
	else
		set_char(arg, pattern, astrsk_c, quote_c);
}

/**
 * It sets the asterix inside the pattern string 
 * to a literal asterix
 * 
 * @param pattern The pattern to be parsed.
 */
static void	set_literal_astrsk(char **pattern)
{
	**pattern = '\'';
	(*pattern)++;
	**pattern = '*';
	(*pattern)++;
	**pattern = '\'';
}
