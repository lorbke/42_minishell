/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:23:27 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, free, ft_strlen
#include "globber/globber.h" // globber
#include "expander_private.h" // ft_realloc, expand_var, get_var, add_expanded_var, handle_single_quotes, quote_removal

static char	*try_expansion(char *result, char *arg, int *index, int *result_index);
static char	*add_char_to_string(char *result, char c, int *index, int *result_index);

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
				result = try_expansion(result, argv[i], &j, &result_index);
			else if (argv[i][j] == '\'')
				result = handle_quotes(result, argv[i], &j, &result_index);
			else
				result = add_char_to_string(result, argv[i][j], &j, &result_index);
		}
		argv[i] = result;
		i++;
	}
	argv = globber(argv);
	return (argv);
}

static char *try_expansion(char *result, char *arg, int *index, int *result_index)
{
	char	*var;
	char	*value;
	char	*expanded_var;

	(*index)++;
	expanded_var = NULL;
	var = get_var(&arg[*index], &(*index));
	if (var == NULL)
		return (NULL);
	value = expand_var(var);
	if (value != NULL)
	{
		expanded_var = add_expanded_var(result, value, &(*result_index));
		free(value);
	}
	free(var);
	return (expanded_var);
}

static char	*add_char_to_string(char *result, char c, int *index, int *result_index)
{
	char *arg;

	(*index)++;
	if (result == NULL)
		arg = malloc(sizeof(char) * 2);
	else
		arg = ft_realloc(result, ft_strlen(result) + 2);
	arg[(*result_index)++] = c;
	arg[*result_index] = '\0';
	return (arg);
}
