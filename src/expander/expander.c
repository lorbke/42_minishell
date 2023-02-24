/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/24 18:39:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // NULL, malloc, free, ft_strlen, ft_strdup
#include "../expander.h" // expander, expand_str
#include "globber/globber.h" // globber
#include "../utils.h" // ft_realloc
#include "expander_private.h" // handle_quotes, try_expansion, tilde_expansion, add_char_to_str, in_closed_quotes

static char	**copy_argv(char **argv);
static char	*eval_char(char *result, char *arg, int *index, int *result_index);

#include <stdio.h>

char	**expander(char **argv)
{
	int		i;
	int		k;
	char	*result;
	char	**new_argv;

	i = 1;
	k = 1;
	new_argv = copy_argv(argv);
	result = expand_str(new_argv[0]);
	if (result != NULL)
	{
		free(new_argv[0]);
		new_argv[0] = result;
	}
	while (new_argv[i] != NULL)
	{
		result = expand_str(new_argv[i]);
		if (result != NULL)
		{
			free(new_argv[i]);
			new_argv[k] = result;
			k++;
		}
		i++;
	}
	new_argv[k] = NULL;
	k = 0;
	while (new_argv[k] != NULL)
	{
		result = new_argv[k];
		new_argv[k] = ft_strtrim(new_argv[k], " ");
		if (new_argv[k])
			free(result);
		// printf("new_argv[%d] = %s\n", k, new_argv[k]);
		k++;
	}
	new_argv = globber(new_argv);
	return (new_argv);
}

char	*expand_str(char *arg)
{
	char	*result;
	int		i;
	int		result_index;

	result = NULL;
	i = 0;
	result_index = 0;
	while (arg[i] != '\0')
		result = eval_char(result, arg, &i, &result_index);
	return (result);
}

char	*add_char_to_str(char *result, char c, int *index, int *result_index)
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

static char	*eval_char(char *result, char *arg, int *index, int *result_index)
{
	static int	d_quotes;

	if (arg[*index] == '$' && arg[*index + 1] != '\0' && ft_isspace(arg[*index + 1]) == 0)
	{
		if (in_closed_quotes(result, arg, &(*index), &(*result_index)))
		{
			result = add_char_to_str(result, arg[*index], &(*index), &(*result_index));
			return (result);
		}
		result = try_expansion(result, arg, &(*index), &(*result_index));
	}
	else if (arg[*index] == '\'')
	{
		if (d_quotes == 1)
			result = add_char_to_str(result, arg[*index], &(*index), &(*result_index));
		else
			result = handle_quotes(result, arg, &(*index), &(*result_index));
	}
	else if (arg[*index] == '~')
		result = tilde_expansion(result, arg, &(*index), &(*result_index));
	else if (arg[*index] == '"')
	{
		if (d_quotes == 0)
			d_quotes = 1;
		else
			d_quotes = 0;
		result = add_char_to_str(result, arg[*index], &(*index), &(*result_index));
		// (*index)++;
	}
	else
	{
		result = add_char_to_str(result, arg[*index], &(*index), &(*result_index));
	}
	return (result);
}

