/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:29:31 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/14 15:29:06 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL
#include "globber.h" // globbing, is_match, concatentate_entries, add_matching_entries, find_pattern, opendir, readdir, closedir
#include "../expander_private.h" // find_closing_quote, quote_removal

static char	**globbing(char *arg, int *index);
char		**globbing_outside_cwd(char *path, char *pattern, char **result);

char	**globber(char **argv)
{
	int		i;
	int		j;
	char	**result;
	char	**expanded_argv;

	i = 1;
	expanded_argv = NULL;
	while (argv[i])
	{
		result = NULL;
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'' || argv[i][j] == '\"')
				find_closing_quote(argv[i], &j, argv[i][j]);
			else if (argv[i][j] == '*')
				result = globbing(argv[i], &j);
			j++;
		}
		expanded_argv = add_vars(expanded_argv, result, &argv[i]);
		i++;
	}
	expanded_argv = create_new_cmd(expanded_argv, argv);
	quote_removal(expanded_argv);
	return (expanded_argv);
}

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

static char **globbing(char *arg, int *index)
{
	char			*pwd;
	char			*pattern;
	char			**result;
	DIR				*dir;
	struct dirent	*entry;
	struct stat		buf;

	result = NULL;
	pattern = find_pattern(arg, &(*index));
	/* parse pattern */
	int i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		char *new_path = ft_substr(pattern, 0, i + 1);
		if (ft_strcmp(new_path, "*/") == 0)
		{
			pwd = getcwd(NULL, 0);
			dir = opendir(pwd);
			char *new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
			while (1)
			{
				entry = readdir(dir);
				if (entry == NULL)
					break ;
				if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
				{
					if (entry->d_type == DT_DIR)
					{
						new_path = ft_strjoin(entry->d_name, "/");
						result = globbing_outside_cwd(new_path, new_pattern, result);
						free(new_path);
					}
				}
			}
			closedir(dir);
			return (result);
		}
		else
		{
			int check = stat(new_path, &buf);
			char *new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
			result = globbing_outside_cwd(new_path, new_pattern, result);
		}
	}
	/* parse pattern */
	pwd = getcwd(NULL, 0);
	dir = opendir(pwd);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
		{
			if (is_match(entry->d_name, pattern))
				result = add_matching_entry(result, entry->d_name);
		}
	}
	closedir(dir);
	free(pattern);
	return (result);
}


char	**globbing_outside_cwd(char *path, char *pattern, char **result)
{
	DIR				*dir;
	char			*pwd;
	char			**new_result;
	char			*new_path;
	char			*new_pattern;
	struct dirent	*entry;
	struct stat		buf;

	int i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		new_path = ft_substr(pattern, 0, i + 1);
		if (ft_strcmp(new_path, "*/") == 0)
		{
			// @note should always be the case
			pwd = path;
			dir = opendir(pwd);
			new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
			int j = 0;
			while (1)
			{
				entry = readdir(dir);
				if (entry == NULL)
					break ;
				if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
				{
					if (entry->d_type == DT_DIR)
					{
						if (new_pattern[0] == '\0')
						{
							if (result != NULL)
							{
								int k = 0;
								while (result[k] != NULL)
									k++;
								new_result = realloc_string_array(result, 2);
								new_result[k] = ft_strjoin(path, entry->d_name);
								new_result[k] = ft_strjoin(new_result[k], "/");
								new_result[k + 1] = NULL;
								result = new_result;
							}
							else
							{
								new_result = malloc(sizeof(char *) * 2);
								new_result[0] = ft_strjoin(path, entry->d_name);
								new_result[0] = ft_strjoin(new_result[0], "/");
								new_result[1] = NULL;
								result = new_result;
							}
						}
						else
						{
							new_path = ft_strjoin(path, entry->d_name);
							new_path = ft_strjoin(new_path, "/");
							result = globbing_outside_cwd(new_path, new_pattern, result);
							free(new_path);
						}
					}
				}
			}
			closedir(dir);
			if (result == NULL)
			{
				printf("no directories found\n");
				return (NULL);
			}
			return (result);
		}
		else
		{
			new_path = ft_strjoin(path, new_path);
			int check = stat(new_path, &buf);
			char *new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
			result = globbing_outside_cwd(new_path, new_pattern, result);
			return (result);
		}
	}
	else
	{
		// if "normal" pattern
		int i = 0;
		pwd = path;
		char *new_entry;
		dir = opendir(pwd);
		while (1)
		{
			entry = readdir(dir);
			if (entry == NULL)
				break ;
			if (entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
			{
				if (is_match(entry->d_name, pattern))
				{
					new_entry = ft_strjoin(path, entry->d_name);
					result = add_matching_entry(result, new_entry);
					i++;
				}
			}
		}
		closedir(dir);
	}
	return (result);
}
