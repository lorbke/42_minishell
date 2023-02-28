/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:20:36 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:25:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, free, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber_private.h" // is_match, opendir, readdir, closedir
#include "../../utils.h" // realloc_string_array, ft_strcmp

static char	**sort_entries(char **result, char *entry);
static char	**add_first_entry(char *entry, char **result);
static char	**add_match(char **result, char *entry, char *path, char *pattern);

/**
 * It adds a new entry to the list of matching entries, and sorts the list
 * 
 * @param result the array of strings that will be returned
 * @param entry the entry to add to the array
 * 
 * @return A string array of all the matching entries.
 */
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

/**
 * It adds the first entry to the result array.
 * 
 * @param path The path to the directory.
 * @param pattern The pattern to match against.
 * @param result a pointer to a pointer to a char.
 * 
 * @return A pointer to a pointer to a char.
 */
char	**get_matching_entries(char *path, char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;

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

/**
 * It adds the first entry to the result array.
 * 
 * @param result a pointer to a pointer to a char.
 * @param entry the string to add to the array
 * @param path the path to the directory
 * @param pattern The pattern to match against.
 * 
 * @return A pointer to a pointer to a char.
 */
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

/**
 * It adds the first entry to the result array
 * 
 * @param entry the string to add to the array
 * @param result the array of strings that will be returned
 * 
 * @return A pointer to a pointer to a char.
 */
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

/**
 * It takes a list of strings, and a new string, and inserts 
 * the new string into the list in
 * alphabetical order
 * 
 * @param result the array of strings that will be returned
 * @param entry the name of the file/directory
 * 
 * @return A pointer to a char array.
 */
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
