/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/21 18:14:27 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen
#include "globber_private.h" // globbing, is_match, concatentate_entries, add_matching_entries, find_pattern, opendir, readdir, closedir, create_new_path
#include "../../utils.h" // realloc_string_array, get_string_array_len

static void	check_char(char **arg, char **pattern, int *astrisk_control);
static void	get_next_pattern_char(char *entry, char *pattern, int *index, char *match);

#include <stdio.h>
char	*find_pattern(char *arg, int *index)
{
	char 	*tmp;
	char	*pattern;
	int		astrisk_control;

	pattern = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (pattern == NULL)
		return (NULL);
	tmp = pattern;
	astrisk_control = 0;
	while (*arg != '\0')
	{
		check_char(&arg, &pattern, &astrisk_control);
		(*index)++;
	}
	*pattern = '\0';
	pattern = tmp;
	return (pattern);
}

int	check_match_validity(char *pattern, char *entry, int *i, int *j)
{
	if (*j != 0 && pattern[*j] != '\0')
	{
		if (pattern[*j - 1] != '*')
		{
			if (pattern[*j - 1] == entry[*i - 1])
				(*j)++;
			else
				return (0);
		}
		else
			(*j)++;
	}
	else if (pattern[*j] != '\0')
		(*j)++;
	(*i)++;
	return (1);
}

int	is_match(char *entry, char *pattern)
{
	int		i;
	int		j;
	char	match;

	i = 0;
	// @note maybe rename to p_index?
	j = 0;
	match = 0;
	while(entry[i] != '\0')
	{
		get_next_pattern_char(entry, pattern, &j, &match);
		if (j == 0 && entry[i] != pattern[j])
			break ;
		while (entry[i] != '\0' && entry[i] != match)
			i++;
		if (entry[i] == match)
		{
			if (check_match_validity(pattern, entry, &i, &j) == 0)
				break ;
		}
	}
	if ((pattern[j] == '\0' || pattern[ft_strlen(pattern) - 1] == '*') &&
		(entry[i - 1] == match || match == '*'))
		return (1);
	return (0);
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

static void	check_char(char **arg, char **pattern, int *astrisk_control)
{
	if (**arg == '\'' || **arg == '\"')
		(*arg)++;
	else if (**arg == '*' && *astrisk_control == 0)
	{
		*astrisk_control = 1;
		**pattern = **arg;
		(*arg)++;
		(*pattern)++;
	}
	else
	{
		if (**arg != '*')
		{
			*astrisk_control = 0;
			**pattern = **arg;
			(*pattern)++;
		}
		(*arg)++;
	}
}

static void	get_next_pattern_char(char *entry, char *pattern, int *index, char *match)
{
	if (pattern[*index] != '*' && pattern[*index] != '\0')
		*match = pattern[*index];
	else
	{
		while (pattern[*index] == '*' && pattern[*index] != '\0')
		{
			*match = pattern[*index];
			(*index)++;
		}
		if (pattern[*index] != '\0')
			*match = pattern[*index];
	}
}
