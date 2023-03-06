/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:47:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/03/04 20:42:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table, env_get_value
#include "libft.h" // NULL, malloc, free, ft_isalpha, ft_isalnum, ft_strlen,
// ft_strncmp, ft_strchr, ft_strlcat, ft_strlcpy
#include "../utils.h" // utils_check_naming_convention, utils_ft_realloc
#include "expander_private.h" // expander_char_to_str

/**
 * It expands the tilde character to the user's home directory
 *
 * @param result the string that will be returned
 * @param arg the string to be expanded
 * @param i the index of the current character in the argument
 * @param result_i the index of the result string
 *
 * @return a pointer to a string.
 */
char	*tilde_expansion(char *result, char *arg, int *i, int *result_i)
{
	char	*home;
	char	*expanded_home;

	home = expand_var("HOME");
	if ((result || arg[*i + 1] != '/') && ft_strlen(arg) > 1)
		expanded_home = expander_char_to_str(result, '~', &(*i), &(*result_i));
	else if (home != NULL)
	{
		expanded_home = add_expanded_var(result, home, &(*result_i));
		(*i)++;
	}
	else
		expanded_home = expander_char_to_str(result, '~', &(*i), &(*result_i));
	return (expanded_home);
}

/**
 * It takes a string, a variable name, and a pointer to an integer,
 * and returns a string with the variable expanded
 *
 * @param result the string that will be returned
 * @param var the variable to be expanded
 * @param result_i the index of the result string
 *
 * @return A pointer to a string.
 */
char	*add_expanded_var(char *result, char *var, int *result_i)
{
	char	*arg;

	if (result == NULL)
		arg = ft_strdup(var);
	else
	{
		arg = ft_strjoin(result, var);
		free(result);
	}
	*result_i = ft_strlen(arg);
	return (arg);
}

/**
 * It takes a string and an index, and returns a string containing
 * the variable name
 *
 * @param arg The string that contains the variable name.
 * @param i the index of the argument
 *
 * @return a pointer to a string.
 */
char	*get_var(char *arg, int *i)
{
	int		j;
	char	*var;

	j = utils_check_naming_convention(arg);
	if (j == 0)
	{
		var = malloc(sizeof(char) * ft_strlen(arg) - 1);
		if (var == NULL)
			return (NULL);
		(*i)++;
		ft_strlcpy(var, &arg[*i], ft_strlen(arg));
		return (var);
	}
	var = malloc(sizeof(char) * (j + 1));
	if (var == NULL)
		return (NULL);
	ft_strlcpy(var, arg, (j + 1));
	*i += j;
	return (var);
}

/**
 * It takes a string as an argument, and returns a string
 *
 * @param arg The argument to be expanded.
 *
 * @return The value of the variable.
 */
char	*expand_var(char *arg)
{
	t_sym_tab	*temp;
	size_t		len;
	char		*value;

	temp = *g_sym_table;
	value = NULL;
	while (temp != NULL)
	{
		len = 0;
		while (temp->var[len] != '\0' && temp->var[len] != '=')
			len++;
		if (ft_strlen(arg) > len)
			len = ft_strlen(arg);
		if (ft_strncmp(arg, temp->var, len) == 0)
		{
			if (ft_strchr(temp->var, '=') != NULL)
				value = env_get_value(temp->var);
			else
				value = NULL;
			break ;
		}
		temp = temp->next;
	}
	return (value);
}
