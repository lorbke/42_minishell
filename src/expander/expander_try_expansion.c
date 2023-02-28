/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_try_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:00:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:39:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h> // NULL, malloc, free, ft_strlcpy
#include "expander_private.h" // get_var, add_expanded_var, expand_var

static char	*set_exit_status_var(int *i);
static void	trim_whitespaces(char *expanded_var, char *result);

/**
 * It takes a string,
 * expands any variables in it, and returns the expanded string
 * 
 * @param result the string that will be returned
 * @param arg the argument to be expanded
 * @param i the index of the current character in the argument
 * @param result_i the index of the result string
 * 
 * @return The result of the expansion.
 */
char	*try_expansion(char *result, char *arg, int *i, int *result_i)
{
	char	*var;
	char	*value;
	char	*expanded_var;

	(*i)++;
	expanded_var = result;
	if (arg[(*i)] == '?')
		var = set_exit_status_var(&(*i));
	else if (arg[(*i)] == '\'' || arg[(*i)] == '"')
		return (result);
	else
		var = get_var(&arg[*i], &(*i));
	if (var == NULL)
		return (NULL);
	value = expand_var(var);
	if (value != NULL && value[0] != '\0')
	{
		trim_whitespaces(value, result);
		expanded_var = add_expanded_var(result, value, &(*result_i));
		free(value);
	}
	else
		free(value);
	free(var);
	return (expanded_var);
}

/**
 * It returns a string containing the exit status of the last command executed
 * 
 * @param i the index of the current character in the string
 * 
 * @return A pointer to a string containing the exit status of the last command.
 */
static char	*set_exit_status_var(int *i)
{
	char	*var;

	var = malloc(sizeof(char) * 2);
	if (var == NULL)
		return (NULL);
	ft_strlcpy(var, "?", 2);
	(*i)++;
	return (var);
}

/**
 * It removes all the whitespaces from the beginning of the string and 
 * all the whitespaces that are next to each other
 * 
 * @param expanded_var The variable that has been expanded.
 * @param result the result of the expansion
 */
static void	trim_whitespaces(char *expanded_var, char *result)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (result == NULL)
	{
		while (expanded_var[i] == ' ')
			i++;
	}
	while (expanded_var[i] != '\0')
	{
		if (expanded_var[i] == ' ' && expanded_var[i + 1] == ' ')
			i++;
		else
		{
			expanded_var[j] = expanded_var[i];
			i++;
			j++;
		}
	}
	expanded_var[j] = '\0';
}
