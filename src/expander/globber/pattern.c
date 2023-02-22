/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:17:44 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 13:47:50 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen
#include "globber_private.h" // create_new_path
#include "../../utils.h" // realloc_string_array, get_string_array_len

static void	check_char(char **arg, char **pattern, int *astrisk_control, int *quote_control);

char	*find_pattern(char *arg, int *index)
{
	char 	*tmp;
	char	*pattern;
	int		quote_control;
	int		astrisk_control;

	pattern = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (pattern == NULL)
		return (NULL);
	tmp = pattern;
	quote_control = 0;
	astrisk_control = 0;
	while (*arg != '\0')
	{
		check_char(&arg, &pattern, &astrisk_control, &quote_control);
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

void	set_next_pattern_char(char **arg, char **pattern, int *astrisk_control, int *quote_control)
{
	if (**arg == '*' && *astrisk_control == 0)
	{
		if (*quote_control == 0)
		{
			*astrisk_control = 1;
			**pattern = **arg;
		}
		else
			**pattern = '\'';
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

static void	check_char(char **arg, char **pattern, int *astrisk_control, int *quote_control)
{
	if (**arg == '\'' || **arg == '\"')
	{
		if (*quote_control == 0)
			*quote_control = 1;
		else
			*quote_control = 0;
		*astrisk_control = 0;
		(*arg)++;
	}
	else
		set_next_pattern_char(arg, pattern, astrisk_control, quote_control);
}
