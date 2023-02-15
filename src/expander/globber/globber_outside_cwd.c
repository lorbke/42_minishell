/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_outside_cwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 09:08:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL
#include "globber.h" // globbing, is_match, concatentate_entries, add_matching_entries, find_pattern, opendir, readdir, closedir
#include "../expander_private.h" // find_closing_quote, quote_removal

static char	**expand_cwd_dir(char *path, char *pattern, char **result);
static char	**iterate_over_dir(char *path, char *pattern, char **result);
static char	**expand_in_valid_path(char *path, char *pattern, char **result);

char	**globbing_outside_cwd(char *path, char *pattern, char **result)
{
	int		i;
	char	*new_path;
	char	*new_pattern;
	char	**new_result;

	i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		new_path = ft_substr(pattern, 0, i + 1);
		new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
		if (ft_strcmp(new_path, "*/") == 0)
			result = iterate_over_dir(path, new_pattern, result);
		else
		{
			path = ft_strjoin(path, new_path);
			result = expand_in_valid_path(path, new_pattern, result);
		}
	}
	else
		result = get_matching_entries(path, pattern, result);
	return (result);
}

char	**check_for_path(char *pattern, char **result)
{
	int				i;
	struct stat		buf;
	char			*new_path;
	char			*new_pattern;

	i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		new_path = ft_substr(pattern, 0, i + 1);
		new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
		if (ft_strcmp(new_path, "*/") == 0)
			result = expand_cwd_dir(new_path, new_pattern, result);
		else
		{
			if (stat(new_path, &buf) == 0)
				result = globbing_outside_cwd(new_path, new_pattern, result);
		}
	}
	return (result);
}

static char	**iterate_over_dir(char *path, char *pattern, char **result)
{
	DIR				*dir;
	char			*new_path;
	struct dirent	*entry;

	dir = opendir(path);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if ((entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
			&& entry->d_type == DT_DIR)
		{
			if (pattern[0] == '\0')
				result = pattern_over(result, entry->d_name, path);
			else
			{
				// @note I am sure this will leak, because of the inner strjoin
				new_path = ft_strjoin(ft_strjoin(path, entry->d_name), "/");
				result = globbing_outside_cwd(new_path, pattern, result);
				free(new_path);
			}
		}
	}
	closedir(dir);
	return (result);
}

static char	**expand_in_valid_path(char *path, char *pattern, char **result)
{
	struct stat		buf;

	if (stat(path, &buf) == 0)
		result = globbing_outside_cwd(path, pattern, result);
	free(path);
	return (result);
}

static char	**expand_cwd_dir(char *path, char *pattern, char **result)
{
	DIR				*dir;
	struct dirent	*entry;

	// @note need to protect/check if dir == NULL?
	dir = opendir(getcwd(NULL, 0));
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
		{
			path = ft_strjoin(entry->d_name, "/");
			if (entry->d_type == DT_DIR && pattern[0] != '\0')
				result = globbing_outside_cwd(path, pattern, result);
			else if (entry->d_type == DT_DIR)
				result = add_matching_entry(result, path);
			free(path);
		}
	}
	closedir(dir);
	return (result);
}
