/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:04:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:39:54 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "globber.h"
#include "../expander_private.h"

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

char	**create_new_cmd(char **expanded_argv, char **argv)
{
	int len;

	len = 0;
	if (expanded_argv == NULL)
		return (argv);
	expanded_argv = realloc_string_array(expanded_argv, 1);
	while (expanded_argv[len])
		len++;
	expanded_argv[len + 1] = NULL;
	while (len > 0)
	{
		expanded_argv[len] = expanded_argv[len - 1];
		len--;
	}
	expanded_argv[0] = argv[0];
	return (expanded_argv);
}

// @note as discussed with luca, *every* arg from the cmd will be copied into the expanded_argv
static char	**add_unglobbed_vars(char **expanded_argv, char **result, char **argv)
{
	int i;

	i = 0;
	if (expanded_argv != NULL)
	{
		expanded_argv = realloc_string_array(expanded_argv, 2);
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
		while (result[i])
			i++;
		expanded_argv = realloc_string_array(expanded_argv, i);
		i = 0;
		while (expanded_argv[i])
			i++;
		while (result[j])
		{
			expanded_argv[i + j] = result[j];
			j++;
		}
		expanded_argv[i + j] = NULL;
	}
	return (expanded_argv);
}
