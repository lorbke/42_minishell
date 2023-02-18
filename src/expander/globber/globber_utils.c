/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:04:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/18 10:54:24 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_strlcpy, ft_strjoin
#include "globber_private.h" // struct dirent
#include "../../utils.h" // ft_strcmp
#include "../expander_private.h" // realloc_string_array

static char	**add_globbed_vars(char **expanded_argv, char **result);
static char	**add_unglobbed_vars(char **expanded_argv, char **result, char **argv);
static int	get_string_array_len(char **array);

char **add_vars(char **expanded_argv, char **result, char **argv)
{
	if (result != NULL)
		expanded_argv = add_globbed_vars(expanded_argv, result);
	else
		expanded_argv = add_unglobbed_vars(expanded_argv, result, argv);
	return (expanded_argv);
}

int	is_valid_entry(struct dirent *entry, char *pattern)
{
	if ((entry->d_name[0] != '.' || ft_strcmp(pattern, ".*") == 0)
	&& entry->d_type == DT_DIR)
	{
		return (1);
	}
	return (0);
}

// @note as discussed with luca, *every* arg from the cmd will be copied into the expanded_argv
static char	**add_unglobbed_vars(char **expanded_argv, char **result, char **argv)
{
	int i;

	i = 0;
	if (expanded_argv != NULL)
	{
		expanded_argv = realloc_string_array(expanded_argv, 1);
		i = get_string_array_len(expanded_argv);
	}
	else
		expanded_argv = malloc(sizeof(char *) * 2);
	expanded_argv[i] = malloc(sizeof(char) * ft_strlen(*argv) + 1);
	ft_strlcpy(expanded_argv[i], *argv, ft_strlen(*argv) + 1);
	expanded_argv[i + 1] = NULL;
	return (expanded_argv);
}

static char	**add_globbed_vars(char **expanded_argv, char **result)
{
	int	i;
	int	j;

	j = 0;
	if (expanded_argv == NULL)
		expanded_argv = result;
	else
	{
		i = get_string_array_len(result);
		expanded_argv = realloc_string_array(expanded_argv, i);
		i = get_string_array_len(expanded_argv);
		while (result[j] != NULL)
		{
			expanded_argv[i + j] = malloc(sizeof(char) * ft_strlen(result[j]) + 1);
			ft_strlcpy(expanded_argv[i + j], result[j], ft_strlen(result[j]) + 1);
			free(result[j]);
			j++;
		}
		free(result);
		expanded_argv[i + j] = NULL;
	}
	return (expanded_argv);
}

static int	get_string_array_len(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
