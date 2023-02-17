/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:04:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/17 13:26:00 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, free, ft_strlen, ft_strlcpy, ft_strjoin
#include "../expander_private.h" // realloc_string_array

static char	**add_globbed_vars(char **expanded_argv, char **result);
static char	**add_unglobbed_vars(char **expanded_argv, char **result, char **argv);

char **add_vars(char **expanded_argv, char **result, char **argv)
{
	if (result != NULL)
		expanded_argv = add_globbed_vars(expanded_argv, result);
	else
		expanded_argv = add_unglobbed_vars(expanded_argv, result, argv);
	return (expanded_argv);
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

// @note as discussed with luca, *every* arg from the cmd will be copied into the expanded_argv
static char	**add_unglobbed_vars(char **expanded_argv, char **result, char **argv)
{
	int i;

	i = 0;
	if (expanded_argv != NULL)
	{
		expanded_argv = realloc_string_array(expanded_argv, 1);
		while (expanded_argv[i])
			i++;
	}
	else
		expanded_argv = malloc(sizeof(char *) * 2);
	expanded_argv[i] = malloc(sizeof(char) * ft_strlen(*argv) + 1);
	ft_strlcpy(expanded_argv[i], *argv, ft_strlen(*argv) + 1);
	expanded_argv[i + 1] = NULL;
	return (expanded_argv);
}

// @note shorten
static char	**add_globbed_vars(char **expanded_argv, char **result)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (expanded_argv == NULL)
		expanded_argv = result;
	else
	{
		while (result[i] != NULL)
			i++;
		expanded_argv = realloc_string_array(expanded_argv, i);
		i = 0;
		while (expanded_argv[i] != NULL)
			i++;
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
