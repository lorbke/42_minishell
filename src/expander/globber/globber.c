/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:29:31 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:40:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, free, ft_substr
#include "../../utils.h" // utils_free_split, utils_ft_strcmp
#include "globber_private.h" // is_match, concatentate_entries,
// add_matching_entries, find_pattern, opendir, readdir, closedir,
// expand_cwd_dir, globbing_outside_cwd
#include "../expander_private.h" // quotes_find_closing_quote, quote_removal

static char	**globbing(char *arg, int *i);
static char	**check_for_path(char *pattern, char **result);

/**
 * It takes an array of strings, and returns an array of 
 * strings with the globbing characters expanded
 * 
 * @param argv The original argument vector.
 * 
 * @return a pointer to a pointer to a char.
 */
char	**globber(char **argv)
{
	int		i;
	int		j;
	char	**result;
	char	**exp_argv;

	i = 0;
	exp_argv = NULL;
	while (argv[i] != NULL)
	{
		result = NULL;
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '\'' || argv[i][j] == '\"')
				quotes_find_closing_quote(argv[i], &j, argv[i][j]);
			else if (argv[i][j] == '*')
				result = globbing(argv[i], &j);
			j++;
		}
		exp_argv = add_vars(exp_argv, result, &argv[i]);
		i++;
	}
	quote_removal(exp_argv);
	utils_free_split(argv);
	return (exp_argv);
}

/**
 * It takes a string and an index, finds the pattern in 
 * the string starting at the index, checks for a
 * path, and returns a list of matching entries
 * 
 * @param arg the argument to be globbed
 * @param i the index of the current argument
 * 
 * @return A list of files that match the pattern.
 */
static char	**globbing(char *arg, int *i)
{
	char	*pattern;
	char	**result;

	result = NULL;
	pattern = find_pattern(arg, &(*i));
	result = check_for_path(pattern, result);
	if (ft_strncmp(pattern, "*/", ft_strlen("*/")) != 0)
		result = get_matching_entries(NULL, pattern, result);
	free(pattern);
	return (result);
}

/**
 * It checks if the pattern contains a path, and if so, 
 * it expands the pattern in the path
 * 
 * @param pattern the pattern to be expanded
 * @param result the array of strings that will be returned
 * 
 * @return The result of the globbing.
 */
static char	**check_for_path(char *pattern, char **result)
{
	int				i;
	char			*new_path;
	char			*new_pattern;
	struct stat		buf;

	i = 0;
	while (pattern[i] != '\0' && pattern[i] != '/')
		i++;
	if (pattern[i] == '/')
	{
		new_path = ft_substr(pattern, 0, i + 1);
		new_pattern = ft_substr(pattern, i + 1, ft_strlen(pattern));
		if (ft_strncmp(new_path, "*/", ft_strlen("*/")) == 0)
			result = expand_cwd_dir(new_path, result);
		else if (stat(new_path, &buf) == 0)
			result = globbing_outside_cwd(new_path, new_pattern, result);
		free(new_path);
		free(new_pattern);
	}
	return (result);
}

/**
 * It takes a filename,
 * globbers it, and returns the filename if there's only one match, or NULL if
 * there's more than one match
 * 
 * @param filename The filename to glob.
 * 
 * @return The filename is being returned.
 */
char	*globber_redirection(char *filename)
{
	char	**result;
	int		len;

	result = malloc(sizeof(char *) * 2);
	result[0] = ft_strdup(filename);
	result[1] = NULL;
	result = globber(result);
	len = utils_get_str_array_len(result);
	if (len == 1)
	{
		free(filename);
		filename = ft_strdup(result[0]);
	}
	else if (len > 1)
	{
		free(filename);
		utils_free_split(result);
		return (NULL);
	}
	utils_free_split(result);
	return (filename);
}
