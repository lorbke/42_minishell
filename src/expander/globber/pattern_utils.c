/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:29:57 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 13:54:43 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen

static void	get_next_pattern_char(char *entry, char *pattern, int *index, char *match);
static int	check_match_validity(char *pattern, char *entry, int *i, int *p_index);

int	is_match(char *entry, char *pattern)
{
	int		i;
	int		p_index;
	char	match;

	i = 0;
	p_index = 0;
	match = 0;
	get_next_pattern_char(entry, pattern, &p_index, &match);
	while(entry[i] != '\0')
	{
		if (p_index == 0 && entry[i] != pattern[p_index])
			break ;
		while (entry[i] != '\0' && entry[i] != match)
			i++;
		if (entry[i] == match)
		{
			if (check_match_validity(pattern, entry, &i, &p_index) == 0)
				break ;
		}
		get_next_pattern_char(entry, pattern, &p_index, &match);
	}
	if (pattern[p_index] == '\0' && entry[i] == '\0')
		if (pattern[ft_strlen(pattern) - 1] == '*' || entry[i - 1] == match)
			return (1);
	return (0);
}

static int	check_match_validity(char *pattern, char *entry, int *i, int *p_index)
{
	if (*p_index != 0 && pattern[*p_index] != '\0')
	{
		if (pattern[*p_index - 1] != '*')
		{
			if (pattern[*p_index - 1] == entry[*i - 1])
				(*p_index)++;
			else
				return (0);
		}
		else
			(*p_index)++;
	}
	else if (pattern[*p_index] != '\0')
		(*p_index)++;
	(*i)++;
	return (1);
}

// @note can be changed to "set_match" later on
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
