/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:20:36 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/17 13:31:42 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber.h" // sort_entries
#include "../expander_private.h" // realloc_string_array

static char	**sort_entries(char **result, char *entry);
static char	**add_first_entry(char *entry, char **result);

// @note possible leaks here
// instead of freeing the entry/path inside their repspective functions
// we could do it here
char	**add_matching_entry(char **result, char *entry)
{
	if (result == NULL)
		result = add_first_entry(entry, result);
	else
	{
		result = realloc_string_array(result, 1);
		result = sort_entries(result, entry);
	}
	return (result);
}

// @note ft_join inside here seems to cause leaks
char	**get_matching_entries(char *path, char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*entry_name;

	if (path != NULL)
		dir = opendir(path);
	else
		dir = opendir(getcwd(NULL, 0));
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
		{
			if (is_match(entry->d_name, pattern))
			{
				if (path != NULL)
				{
					entry_name = ft_strjoin(path, entry->d_name);
					result = add_matching_entry(result, entry_name);
					free(entry_name);
				}
				else
				{
					entry_name = malloc(sizeof(char) * ft_strlen(entry->d_name) + 1);
					ft_strlcpy(entry_name, entry->d_name, ft_strlen(entry->d_name) + 1);
					result = add_matching_entry(result, entry_name);
					free(entry_name);
				}
			}
		}
	}
	closedir(dir);
	return (result);
}

static char	**add_first_entry(char *entry, char **result)
{
	result = malloc(sizeof(char *) * 2);
	if (result == NULL)
		return (NULL);
	result[0] = malloc(sizeof(char) * ft_strlen(entry) + 1);
	if (result[0] == NULL)
		return (NULL);
	ft_strlcpy(result[0], entry, ft_strlen(entry) + 1);
	result[1] = NULL;
	return (result);
}

static char	**sort_entries(char **result, char *entry)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (result[len] != NULL)
		len++;
	result[len + 1] = NULL;
	while (result[i] != NULL)
	{
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
	if (result[i] == NULL)
		return (NULL);
	ft_strlcpy(result[i], entry, ft_strlen(entry) + 1);
	return (result);
}
