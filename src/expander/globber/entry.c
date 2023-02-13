/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:20:36 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:45:18 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber.h" // sort_entries
#include "../expander_private.h" // realloc_string_array

static char	**sort_entries(char **result, char *entry);
static char	**add_first_entry(char **result, char *entry);

char	**add_matching_entry(char **result, char *entry)
{
	int		i;
	char	**new_result;

	if (result == NULL)
		new_result = add_first_entry(result, entry);
	else
	{
		new_result = realloc_string_array(result, 1);
		new_result = sort_entries(new_result, entry);
	}
	return (new_result);
}

static char	**add_first_entry(char **result, char *entry)
{
	char **new_result;

	new_result = malloc(sizeof(char *) * 2);
	new_result[0] = malloc(sizeof(char) * ft_strlen(entry) + 1);
	ft_strlcpy(new_result[0], entry, ft_strlen(entry) + 1);
	new_result[1] = NULL;
	return (new_result);
}

static char	**sort_entries(char **result, char *entry)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (result[len])
		len++;
	result[len + 1] = NULL;
	while (result[i])
	{
		// @note write own strcmp
		if (ft_strcmp(entry, result[i]) < 0)
			break ;
		i++;
	}
	while (len > i)
	{
		result[len] = result[len - 1];
		len--;
	}
	result[i] = malloc(sizeof(char) * ft_strlen(entry) + 1);
	ft_strlcpy(result[i], entry, ft_strlen(entry) + 1);
	return (result);
}
