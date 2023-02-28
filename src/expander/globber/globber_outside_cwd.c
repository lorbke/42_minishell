/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_outside_cwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:39:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, free, access, ft_strlen, ft_strlcpy,
// ft_strjoin, ft_substr
#include "globber_private.h" // stat, opendir, readdir, closedir,
// get_matching_entries, create_new_path, pattern_over, is_valid_entry
#include "../expander_private.h" // quotes_find_closing_quote, quote_removal
#include "../../utils.h" // utils_ft_strcmp

static char	**iterate_over_dir(char *path, char *pattern, char **result);
static char	**expand_in_valid_path(char *path, char *pattern, char **result);

/**
 * It takes a path and a pattern, and returns an array of 
 * strings containing all the files in the path
 * that match the pattern
 * 
 * @param path the path to the directory we're currently in
 * @param pattern the pattern to be expanded
 * @param result the array of strings that will be returned
 * 
 * @return An array of strings.
 */
char	**globbing_outside_cwd(char *path, char *pattern, char **result)
{
	int		i;
	char	*new_path;
	char	*new_pattern;

	i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		new_path = ft_substr(pattern, 0, i + 1);
		new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
		if (utils_ft_strcmp(new_path, "*/") == 0)
			result = iterate_over_dir(path, new_pattern, result);
		else
		{
			path = ft_strjoin(path, new_path);
			result = expand_in_valid_path(path, new_pattern, result);
			free(path);
		}
		free(new_path);
		free(new_pattern);
	}
	else if (access(path, R_OK) == 0)
		result = get_matching_entries(path, pattern, result);
	return (result);
}

/**
 * It takes a pattern and a list of matches, and returns a 
 * list of matches that match the pattern
 * 
 * @param pattern the pattern to match
 * @param result the array of strings that will be returned
 * 
 * @return an array of strings.
 */
char	**expand_cwd_dir(char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*new_path;

	dir = opendir(getcwd(NULL, 0));
	while (dir != NULL)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || utils_ft_strcmp(pattern, ".*") == 0)
		{
			new_path = ft_strjoin(entry->d_name, "/");
			if (entry->d_type == DT_DIR && pattern[0] != '\0')
				result = globbing_outside_cwd(new_path, pattern, result);
			else if (entry->d_type == DT_DIR && pattern[0] == '\0')
				result = add_matching_entry(result, new_path);
			free(new_path);
		}
	}
	if (dir != NULL)
		closedir(dir);
	return (result);
}

/**
 * It iterates over a directory, and if the entry is valid, it either 
 * adds it to the result array, or
 * it calls globbing_outside_cwd() on the entry
 * 
 * @param path the path to the directory we're iterating over
 * @param pattern the pattern to match
 * @param result the array of strings that will be returned
 * 
 * @return The result of the globbing.
 */
char	*create_new_path(char *path, char *entry)
{
	char	*sub_path;
	char	*new_path;

	sub_path = ft_strjoin(path, entry);
	new_path = ft_strjoin(sub_path, "/");
	free(sub_path);
	return (new_path);
}

/**
 * It iterates over a directory, and if the entry is valid, it either 
 * adds it to the result array, or
 * it calls globbing_outside_cwd() on the entry
 * 
 * @param path the path to the directory we're iterating over
 * @param pattern the pattern to match
 * @param result the array of strings that will be returned
 * 
 * @return The result of the globbing.
 */
static char	**iterate_over_dir(char *path, char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*new_path;

	dir = opendir(path);
	while (dir != NULL)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (is_valid_entry(entry, pattern))
		{
			if (pattern[0] == '\0')
				result = pattern_over(result, entry->d_name, path);
			else
			{
				new_path = create_new_path(path, entry->d_name);
				result = globbing_outside_cwd(new_path, pattern, result);
				free(new_path);
			}
		}
	}
	if (dir != NULL)
		closedir(dir);
	return (result);
}

/**
 * If the path is valid,
 * then globbing_outside_cwd() is called.
 * 
 * @param path the path to the directory we're currently in
 * @param pattern the pattern to be expanded
 * @param result the array of strings that will be returned
 * 
 * @return The result of the globbing_outside_cwd function.
 */
static char	**expand_in_valid_path(char *path, char *pattern, char **result)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
		result = globbing_outside_cwd(path, pattern, result);
	return (result);
}
