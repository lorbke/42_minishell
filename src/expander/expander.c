/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 14:14:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 19:30:52 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // NULL, malloc, free, ft_strlen, ft_strdup
#include "../expander.h" // expander, expand_str
#include "../globber.h" // globber
#include "../utils.h" // ft_realloc
#include "expander_private.h" // handle_quotes, try_expansion, tilde_expansion,
// add_char_to_str, in_closed_quotes

static char	**copy_argv(char **argv);
static char	*eval_char(char *result, char *arg, int *i, int *result_i);

char	**expander(char **argv)
{
	int		i;
	int		k;
	char	*result;
	char	**new_argv;

	i = 0;
	k = 0;
	new_argv = copy_argv(argv);
	while (new_argv[i] != NULL)
	{
		result = expand_str(new_argv[i]);
		if (result != NULL)
		{
			free(new_argv[i]);
			new_argv[k] = ft_strtrim(result, " ");
			free(result);
			k++;
		}
		i++;
	}
	new_argv[k] = NULL;
	new_argv = globber(new_argv);
	return (new_argv);
}

char	*expand_str(char *arg)
{
	char	*result;
	int		i;
	int		result_i;

	result = NULL;
	i = 0;
	result_i = 0;
	while (arg[i] != '\0')
		result = eval_char(result, arg, &i, &result_i);
	return (result);
}

char	*add_char_to_str(char *result, char c, int *i, int *result_i)
{
	char	*arg;

	(*i)++;
	if (result == NULL)
	{
		arg = malloc(sizeof(char) * 2);
		if (arg == NULL)
			return (NULL);
	}
	else
		arg = ft_realloc(result, ft_strlen(result) + 2);
	arg[(*result_i)++] = c;
	arg[*result_i] = '\0';
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

static char	*eval_char(char *result, char *arg, int *i, int *result_i)
{
	static int	d_quotes;

	if (arg[*i] == '$' && arg[*i + 1] != '\0' && ft_isspace(arg[*i + 1]) == 0)
	{
		if (in_closed_quotes(arg, &(*i)))
			result = add_char_to_str(result, arg[*i], &(*i), &(*result_i));
		else
			result = try_expansion(result, arg, &(*i), &(*result_i));
	}
	else if (arg[*i] == '\'')
	{
		if (d_quotes == 1)
			result = add_char_to_str(result, arg[*i], &(*i), &(*result_i));
		else
			result = handle_quotes(result, arg, &(*i), &(*result_i));
	}
	else if (arg[*i] == '~')
		result = tilde_expansion(result, arg, &(*i), &(*result_i));
	else
	{
		if (arg[*i] == '"')
			d_quotes = !d_quotes;
		result = add_char_to_str(result, arg[*i], &(*i), &(*result_i));
	}
	return (result);
}
