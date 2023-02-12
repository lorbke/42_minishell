/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/12 19:01:24 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, free, ft_strlen
#include "globber/globber.h" // globber
#include "expander_private.h" // ft_realloc, expand_var, get_var, add_expanded_var, handle_single_quotes, quote_removal
#include <stdio.h> // printf

static char	*try_expansion(char *arg, int *index, int *result_index, char *test);
static char	*add_char_to_string(char *result, char c, int *index);

// @note if there already are some values inside result, we need to
// concatenate them with the new (expanded) value (at least it is a problem inside try_expansion)
char	**expander(char **argv)
{
	int		i;
	int		j;
	int		result_index;
	char	*result;

	i = 1;
	while (argv[i])
	{
		result = NULL;
		j = 0;
		result_index = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '$')
				result = try_expansion(&argv[i][j], &j, &result_index, result);
			else if (argv[i][j] == '\'')
				result = handle_quotes(result, &argv[i][j], &j, &result_index);
			else
				result = add_char_to_string(result, argv[i][j++], &result_index);
		}
		argv[i] = result;
		i++;
	}
	argv = globber(argv);
	return (argv);
}

static char *try_expansion(char *arg, int *index, int *result_index, char *test)
{
	char	*var;
	char	*result;
	char	*end_result;

	(*index)++;
	arg++;
	result = NULL;
	end_result = NULL;
	var = get_var(arg, &(*index));
	if (var == NULL)
		return (NULL);
	var = expand_var(var);
	if (var != NULL)
		result = add_expanded_var(result, var, &(*result_index));
	return (result);
}

static char	*add_char_to_string(char *result, char c, int *index)
{
	char *arg;

	if (!result)
		arg = malloc(sizeof(char) * 2);
	else
		arg = ft_realloc(result, ft_strlen(result) + 2);
	arg[(*index)++] = c;
	arg[*index] = '\0';
	return (arg);
}
