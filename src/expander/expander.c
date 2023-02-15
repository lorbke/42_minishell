/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 09:53:27 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, free, ft_strlen
#include "globber/globber.h" // globber
#include "expander_private.h" // ft_realloc, expand_var, get_var, add_expanded_var, handle_single_quotes, quote_removal

static char	*try_expansion(char *result, char *arg, int *index, int *result_index);
static char	*evaluate_char(char *result, char *arg, int *index, int *result_index);
static char	*add_char_to_string(char *result, char c, int *index, int *result_index);
static char	*tilde_expansion(char *result, char *arg, int *index, int *result_index);

char	**expander(char **argv)
{
	int		i;
	int		j;
	int		k;
	int		result_index;
	char	*result;

	i = 1;
	k = 1;
	while (argv[i])
	{
		result = NULL;
		j = 0;
		result_index = 0;
		while (argv[i][j])
			result = evaluate_char(result, argv[i], &j, &result_index);
		if (result != NULL)
		{
			argv[k] = result;
			k++;
		}
		i++;
	}
	argv[k] = NULL;
	argv = globber(argv);
	return (argv);
}

static char	*evaluate_char(char *result, char *arg, int *index, int *result_index)
{
	if (arg[*index] == '$')
		result = try_expansion(result, arg, &(*index), &(*result_index));
	else if (arg[*index] == '\'')
		result = handle_quotes(result, arg, &(*index), &(*result_index));
	else if (arg[*index] == '~')
		result = tilde_expansion(result, arg, &(*index), &(*result_index));
	else
		result = add_char_to_string(result, arg[*index], &(*index), &(*result_index));
	return (result);
}

static char *try_expansion(char *result, char *arg, int *index, int *result_index)
{
	char	*var;
	char	*value;
	char	*expanded_var;

	(*index)++;
	expanded_var = result;
	var = get_var(&arg[*index], &(*index));
	if (var == NULL && result == NULL)
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

static char	*tilde_expansion(char *result, char *arg, int *index, int *result_index)
{
	char	*home;
	char	*expanded_home;

	if ((result || arg[*index + 1] != '/') && ft_strlen(arg) > 1)
	{
		expanded_home = add_char_to_string(result, '~', &(*index), &(*result_index));
		return (expanded_home);
	}
	home = expand_var("HOME");
	expanded_home = add_expanded_var(result, home, &(*result_index));
	free(home);
	(*index)++;
	return (expanded_home);
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
