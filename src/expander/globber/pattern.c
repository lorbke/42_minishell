/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/23 23:39:54 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen
#include "globber_private.h" // create_new_path
#include "../../utils.h" // realloc_string_array, get_string_array_len

static void	scan_char(char **arg, char **pattern, int *asterisk_c, int *quote_c);
static void	set_char(char **arg, char **pattern, int *asterisk_c, int *quote_c);
static void	set_literal_asterisk(char **pattern);

char	*find_pattern(char *arg, int *index)
{
	char 	*tmp;
	char	*pattern;
	int		quote_c;
	int		asterisk_c;

	pattern = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (pattern == NULL)
		return (NULL);
	tmp = pattern;
	quote_c = 0;
	asterisk_c = 0;
	while (*arg != '\0')
	{
		scan_char(&arg, &pattern, &asterisk_c, &quote_c);
		(*index)++;
	}
	*pattern = '\0';
	pattern = tmp;
	return (pattern);
}

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

static void	set_char(char **arg, char **pattern, int *asterisk_c, int *quote_c)
{
	if (**arg == '*' && *asterisk_c == 0)
	{
		if (*quote_c == 0)
		{
			*asterisk_c = 1;
			**pattern = **arg;
		}
		else
			set_literal_asterisk(&(*pattern));
		(*pattern)++;
	}
	else
	{
		if (**arg != '*')
		{
			*asterisk_c = 0;
			**pattern = **arg;
			(*pattern)++;
		}
	}
	(*arg)++;
}

static void	scan_char(char **arg, char **pattern, int *asterisk_c, int *quote_c)
{
	if (**arg == '\'' || **arg == '\"')
	{
		if (*quote_c == 0)
			*quote_c = 1;
		else
			*quote_c = 0;
		*asterisk_c = 0;
		(*arg)++;
	}
	else
		set_char(arg, pattern, asterisk_c, quote_c);
}

static void	set_literal_asterisk(char **pattern)
{
	**pattern = '\'';
	(*pattern)++;
	**pattern = '*';
	(*pattern)++;
	**pattern = '\'';
}
