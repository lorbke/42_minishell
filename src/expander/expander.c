/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/10 08:57:41 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, free, ft_strlen
#include "expander_private.h" // ft_realloc, expand_var, get_var, add_expanded_var, handle_single_quotes, quote_removal

static char	*try_expansion(char *arg, int *index, int *result_index);
static char	*add_char_to_string(char *result, char c, int *index);
static char	*copy_result_to_argv(char *result);

void	expander(char **argv)
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
				result = try_expansion(&argv[i][j], &j, &result_index);
			else if (argv[i][j] == '\'')
				result = handle_single_quotes(result, &argv[i][j], &j, &result_index);
			else
				result = add_char_to_string(result, argv[i][j++], &result_index);
		}
		argv[i] = copy_result_to_argv(result);
		i++;
	}
}

static char *try_expansion(char *arg, int *index, int *result_index)
{
	char	*var;
	char	*result;

	(*index)++;
	arg++;
	result = NULL;
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
		arg = ft_realloc(result, ft_strlen(result));
	arg[(*index)++] = c;
	arg[(*index)] = '\0';
	return (arg);
}

static char	*copy_result_to_argv(char *result)
{
	char	*arg;
	int		i;

	if (result == NULL)
		return (NULL);
	i = 0;
	arg = malloc(sizeof(char) * ft_strlen(result) + 1);
	while (result[i])
	{
		arg[i] = result[i];
		i++;
	}
	arg[i] = '\0';
	quote_removal(arg);
	free(result);
	return (arg);
}
