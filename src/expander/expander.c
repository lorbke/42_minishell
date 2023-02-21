/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/21 14:54:14 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, free, ft_strlen, ft_strdup
#include "globber/globber.h" // globber
#include "../utils.h" // ft_realloc
#include "expander_private.h" // handle_quotes, try_expansion, tilde_expansion, add_char_to_string, in_closed_quotes

static char	**copy_argv(char **argv);
static char	*evaluate_argv(char *arg);
static char	*evaluate_char(char *result, char *arg, int *index, int *result_index);

char	**expander(char **argv)
{
	int		i;
	int		k;
	char	*result;
	char	**new_argv;

	i = 1;
	k = 1;
	new_argv = copy_argv(argv);
	while (new_argv[i] != NULL)
	{
		result = evaluate_argv(new_argv[i]);
		if (result != NULL)
		{
			free(new_argv[i]);
			new_argv[k] = result;
			k++;
		}
		i++;
	}
	new_argv[k] = NULL;
	new_argv = globber(new_argv);
	return (new_argv);
}

char	*add_char_to_string(char *result, char c, int *index, int *result_index)
{
	char *arg;

	(*index)++;
	if (result == NULL)
	{
		arg = malloc(sizeof(char) * 2);
		if (arg == NULL)
			return (NULL);
	}
	else
		arg = ft_realloc(result, ft_strlen(result) + 2);
	arg[(*result_index)++] = c;
	arg[*result_index] = '\0';
	return (arg);
}

static char	**copy_argv(char **argv)
{
	int		len;
	char	**new_argv;

	len = 0;
	while (argv[len] != NULL)
		len++;
	new_argv = malloc(sizeof(char *) * (len + 1));
	if (new_argv == NULL)
		return (NULL);
	len = 0;
	while (argv[len] != NULL)
	{
		new_argv[len] = ft_strdup(argv[len]);
		len++;
	}
	new_argv[len] = NULL;
	return (new_argv);
}

static char	*evaluate_argv(char *arg)
{
	char	*result;
	int		i;
	int		result_index;

	result = NULL;
	i = 0;
	result_index = 0;
	while (arg[i] != '\0')
		result = evaluate_char(result, arg, &i, &result_index);
	return (result);
}

static char	*evaluate_char(char *result, char *arg, int *index, int *result_index)
{
	if (arg[*index] == '$' && arg[*index + 1] != '\0')
	{
		if (in_closed_quotes(result, arg, &(*index), &(*result_index)))
		{
			result = add_char_to_string(result, arg[*index], &(*index), &(*result_index));
			return (result);
		}
		result = try_expansion(result, arg, &(*index), &(*result_index));
	}
	else if (arg[*index] == '\'')
		result = handle_quotes(result, arg, &(*index), &(*result_index));
	else if (arg[*index] == '~')
		result = tilde_expansion(result, arg, &(*index), &(*result_index));
	else
		result = add_char_to_string(result, arg[*index], &(*index), &(*result_index));
	return (result);
}
