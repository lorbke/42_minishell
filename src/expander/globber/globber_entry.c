/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:20:36 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 13:48:00 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, free, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber_private.h" // is_match, opendir, readdir, closedir
#include "../../utils.h" // realloc_string_array, ft_strcmp

static char	**sort_entries(char **result, char *entry);
static char	**add_first_entry(char *entry, char **result);
static char	**add_match(char **result, char *entry, char *path, char *pattern);

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

char	**get_matching_entries(char *path, char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*entry_name;

	if (path != NULL)
		dir = opendir(path);
	else
		dir = opendir(getcwd(NULL, 0));
	while (dir != NULL)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
			result = add_match(result, entry->d_name, path, pattern);
	}
	if (dir != NULL)
		closedir(dir);
	return (result);
}

static char	**add_match(char **result, char *entry, char *path, char *pattern)
{
	char	*entry_name;

	if (is_match(entry, pattern))
	{
		if (path != NULL)
		{
			entry_name = ft_strjoin(path, entry);
			result = add_matching_entry(result, entry_name);
			free(entry_name);
		}
		else
		{
			entry_name = malloc(sizeof(char) * ft_strlen(entry) + 1);
			ft_strlcpy(entry_name, entry, ft_strlen(entry) + 1);
			result = add_matching_entry(result, entry_name);
			free(entry_name);
		}
	}
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
