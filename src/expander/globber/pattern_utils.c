/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:29:57 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 23:08:53 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen

static void	set_match(char *entry, char *pattern, int *index, char *match);
static int	is_match_valid(char *pattern, char *entry, int *i, int *p_index);

int	is_match(char *entry, char *pattern)
{
	int		i;
	int		p_index;
	char	match;

	i = 0;
	p_index = 0;
	match = 0;
	set_match(entry, pattern, &p_index, &match);
	while(entry[i] != '\0')
	{
		if (p_index == 0 && entry[i] != pattern[p_index])
			break ;
		while (entry[i] != '\0' && entry[i] != match)
			i++;
		if (entry[i] == match)
		{
			if (is_match_valid(pattern, entry, &i, &p_index) == 0)
				break ;
		}
		set_match(entry, pattern, &p_index, &match);
	}
	if (pattern[p_index] == '\0' && entry[i] == '\0')
		if (pattern[ft_strlen(pattern) - 1] == '*' || entry[i - 1] == match)
			return (1);
	return (0);
}

static int	is_match_valid(char *pattern, char *entry, int *i, int *p_index)
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

static void	set_match(char *entry, char *pattern, int *index, char *match)
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
