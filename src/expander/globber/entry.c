/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:20:36 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/11 21:28:59 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen, ft_strlcpy, ft_strjoin
#include "../expander_private.h" // realloc_string_array

char	*concatenate_entries(char **result)
{
	int		i;
	char	*concat_string;

	i = 0;
	if (result == NULL)
		return (NULL);
	while (result[i])
	{
		if (i == 0)
		{
			concat_string = malloc(sizeof(char) * ft_strlen(result[i]) + 1);
			ft_strlcpy(concat_string, result[i], ft_strlen(result[i]) + 1);
		}
		else
		{
			concat_string = ft_strjoin(concat_string, result[i]);
			concat_string = ft_strjoin(concat_string, " ");
		}
		i++;
	}
	return (concat_string);
}

char	**add_first_entry(char **result, char *entry)
{
	char **new_result;

	new_result = (char **)malloc(sizeof(char *) * 2);
	new_result[0] = (char *)malloc(sizeof(char) * ft_strlen(entry) + 1);
	ft_strlcpy(new_result[0], entry, ft_strlen(entry) + 1);
	new_result[0] = ft_strjoin(new_result[0], " ");
	new_result[1] = NULL;
	return (new_result);
}

char	**add_matching_entry(char **result, char *entry)
{
	int		i;
	char	**new_result;

	if (result == NULL)
		new_result = add_first_entry(result, entry);
	else
	{
		i = 0;
		while (result[i])
			i++;
		new_result = realloc_string_array(result);
		new_result[i] = malloc(sizeof(char) * ft_strlen(entry) + 1);
		ft_strlcpy(new_result[i], entry, ft_strlen(entry) + 1);
		// @note this seemed to fix the segfault
		new_result[i + 1] = NULL;
	}
	// @note sorting still leads to segfault
	// else
	// {
	// 	new_result = realloc_string_array(result);
	// 	new_result = sort_matching_entries(new_result, entry);
	// }
	return (new_result);
}
