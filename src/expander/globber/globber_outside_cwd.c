/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_outside_cwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:23:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 16:41:21 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, free, access, ft_strlen, ft_strlcpy,
// ft_strjoin, ft_substr
#include "globber_private.h" // stat, opendir, readdir, closedir,
// get_matching_entries, create_new_path, pattern_over, is_valid_entry
#include "../expander_private.h" // find_closing_quote, quote_removal

static char	**iterate_over_dir(char *path, char *pattern, char **result);
static char	**expand_in_valid_path(char *path, char *pattern, char **result);

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
		if (ft_strcmp(new_path, "*/") == 0)
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

static char	**expand_in_valid_path(char *path, char *pattern, char **result)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
		result = globbing_outside_cwd(path, pattern, result);
	return (result);
}

char	**expand_cwd_dir(char *path, char *pattern, char **result)
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
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
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

char	*create_new_path(char *path, char *entry)
{
	char	*sub_path;
	char	*new_path;

	sub_path = ft_strjoin(path, entry);
	new_path = ft_strjoin(sub_path, "/");
	free(sub_path);
	return (new_path);
}
