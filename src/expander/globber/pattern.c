/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 21:30:56 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen
#include "globber_private.h" // create_new_path
#include "../../utils.h" // realloc_string_array, get_string_array_len

static void	scan_char(char **arg, char **pattern, int *astrsk_c, int *quote_c);
static void	set_char(char **arg, char **pattern, int *astrsk_c, int *quote_c);
static void	set_literal_astrsk(char **pattern);

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

static void	set_literal_astrsk(char **pattern)
{
	**pattern = '\'';
	(*pattern)++;
	**pattern = '*';
	(*pattern)++;
	**pattern = '\'';
}
