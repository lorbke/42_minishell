/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_try_expansion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:00:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 20:01:46 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h> // NULL, malloc, free, ft_strlcpy
#include "expander_private.h" // get_var, add_expanded_var, expand_var

static char	*set_exit_status_var(int *i);
static void	trim_whitespaces(char *expanded_var, char *result);

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
