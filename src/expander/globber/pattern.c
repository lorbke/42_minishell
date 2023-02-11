/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/11 21:26:48 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen

static void	get_next_char(char *entry, char *pattern, int *index, char *match);

//@note need to shorten this baby
char	*find_pattern(char *arg, int *index)
{
	int		i;
	int		j;
	char	*pattern;
	int		astrisk_control;

	i = 0;
	j = 0;
	pattern = (char *)malloc(sizeof(char) * ft_strlen(arg));
	astrisk_control = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i++;
		else if (arg[i] == '*' && astrisk_control == 0)
		{
			astrisk_control = 1;
			pattern[j++] = arg[i++];
		}
		else
		{
			if (arg[i] != '*')
			{
				astrisk_control = 0;
				pattern[j] = arg[i];
				j++;
			}
			i++;
		}
		(*index)++;
	}
	pattern[j] = '\0';
	return (pattern);
}

int	is_match(char *entry, char *pattern)
{
	int		i;
	int		j;
	char	match;

	i = 0;
	j = 0;
	match = 0;
	while(entry[i])
	{
		get_next_char(entry, pattern, &j, &match);
		if (j == 0 && entry[i] != pattern[j])
			break ;
		while (entry[i] && entry[i] != match)
			i++;
		if (entry[i] == match)
		{
			i++;
			if (pattern[j] != '\0')
				j++;
		}
	}
	if (pattern[j] == '\0' && (entry[i - 1] == match || match == '*'))
		return (1);
	return (0);
}

static void	get_next_char(char *entry, char *pattern, int *index, char *match)
{
	if (pattern[(*index)] != '*' && pattern[(*index)] != '\0')
		*match = pattern[(*index)];
	else
	{
		while (pattern[(*index)] == '*' && pattern[(*index)] != '\0')
			*match = pattern[(*index)++];
		if (pattern[(*index)] != '\0')
			*match = pattern[(*index)];
	}
}
