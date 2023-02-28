/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:04:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:40:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // NULL, malloc, free, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber_private.h" // struct dirent, DT_DIR
#include "../../utils.h" // utils_realloc_str_arr, utils_ft_strcmp,
// utils_get_str_array_len

static char	**add_globbed_vars(char **exp_argv, char **result);
static char	**add_unglobbed_vars(char **exp_argv, char **argv);

/**
 * It checks if the entry is a directory, and if it is, 
 * it checks if it's a hidden directory or if the
 * pattern is ".*" (which means we want to display hidden directories).
 * 
 * @param entry the current directory entry
 * @param pattern The pattern to match against.
 */
char	**add_vars(char **exp_argv, char **result, char **argv)
{
	if (result != NULL)
		exp_argv = add_globbed_vars(exp_argv, result);
	else
		exp_argv = add_unglobbed_vars(exp_argv, argv);
	return (exp_argv);
}

/**
 * It checks if the entry is a directory, and if it is, 
 * it checks if it's a hidden directory or if the
 * pattern is ".*" (which means we want to display hidden directories).
 * 
 * @param entry the current directory entry
 * @param pattern The pattern to match against.
 */
int	is_valid_entry(struct dirent *entry, char *pattern)
{
	if ((entry->d_name[0] != '.' || utils_ft_strcmp(pattern, ".*") == 0)
		&& entry->d_type == DT_DIR)
	{
		return (1);
	}
	return (0);
}

/**
 * It adds the unglobbed
 * arguments to the array of expanded arguments.
 * 
 * @param exp_argv The array of strings that will be returned.
 * @param argv The argument vector to be expanded.
 * 
 * @return A string array of the unglobbed arguments.
 */
static char	**add_unglobbed_vars(char **exp_argv, char **argv)
{
	int	i;

	i = 0;
	if (exp_argv != NULL)
	{
		exp_argv = utils_realloc_str_arr(exp_argv, 1);
		i = utils_get_str_array_len(exp_argv);
	}
	else
		exp_argv = malloc(sizeof(char *) * 2);
	exp_argv[i] = malloc(sizeof(char) * ft_strlen(*argv) + 1);
	ft_strlcpy(exp_argv[i], *argv, ft_strlen(*argv) + 1);
	exp_argv[i + 1] = NULL;
	return (exp_argv);
}

/**
 * It adds the globbed variables to the array of expanded arguments
 * 
 * @param exp_argv the array of arguments that we're building up
 * @param result the array of strings that were globbed
 * 
 * @return The expanded argument vector.
 */
static char	**add_globbed_vars(char **exp_argv, char **result)
{
	int	i;
	int	j;

	j = 0;
	if (exp_argv == NULL)
		exp_argv = result;
	else
	{
		i = utils_get_str_array_len(result);
		exp_argv = utils_realloc_str_arr(exp_argv, i);
		i = utils_get_str_array_len(exp_argv);
		while (result[j] != NULL)
		{
			exp_argv[i + j] = malloc(sizeof(char) * ft_strlen(result[j]) + 1);
			ft_strlcpy(exp_argv[i + j], result[j], ft_strlen(result[j]) + 1);
			free(result[j]);
			j++;
		}
		free(result);
		exp_argv[i + j] = NULL;
	}
	return (exp_argv);
}
