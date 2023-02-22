/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:47:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 23:33:14 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // NULL, malloc, free, ft_isalpha, ft_isalnum, ft_strlen, ft_strncmp, ft_strchr, ft_strlcat, ft_strlcpy
#include "../utils.h" // check_naming_convention, ft_realloc
#include "expander_private.h" // add_char_to_str

static char	*expand_var(char *arg);
static char	*get_var(char *arg, int *index);
static char	*add_expanded_var(char *result, char *var, int *result_index);

char	*try_expansion(char *result, char *arg, int *index, int *result_index)
{
	char	*var;
	char	*value;
	char	*expanded_var;

	(*index)++;
	expanded_var = result;
	if (arg[(*index)] == '?')
	{
		var = malloc(sizeof(char) * 2);
		if (var == NULL)
			return (NULL);
		ft_strlcpy(var, "?", 2);
		(*index)++;
	}
	else
		var = get_var(&arg[*index], &(*index));
	if (var == NULL)
		return (NULL);
	value = expand_var(var);
	if (value != NULL)
		expanded_var = add_expanded_var(result, value, &(*result_index));
	free(var);
	return (expanded_var);
}

char	*tilde_expansion(char *result, char *arg, int *index, int *result_index)
{
	char	*home;
	char	*expanded_home;

	home = expand_var("HOME");
	if ((result || arg[*index + 1] != '/') && ft_strlen(arg) > 1)
		expanded_home = add_char_to_str(result, '~', &(*index), &(*result_index));
	else if (home != NULL)
	{
		expanded_home = add_expanded_var(result, home, &(*result_index));
		(*index)++;
	}
	else
		expanded_home = add_char_to_str(result, '~', &(*index), &(*result_index));
	return (expanded_home);
}

static char	*expand_var(char *arg)
{
	t_sym_tab	*temp;
	int			len;
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
				value = ft_strchr(temp->var, '=') + 1;
			else
				value = NULL;
			break ;
		}
		temp = temp->next;
	}
	return (value);
}

static char	*add_expanded_var(char *result, char *var, int *result_index)
{
	int		i;
	char	*arg;

	i = 0;
	if (result == NULL)
		arg = ft_strdup(var);
	else
	{
		arg = ft_realloc(result, ft_strlen(result) + ft_strlen(var) + 1);
		ft_strlcat(arg, var, ft_strlen(arg) + ft_strlen(var) + 1);
	}
	*result_index = ft_strlen(arg);
	return (arg);
}

static char	*get_var(char *arg, int *index)
{
	int		i;
	int		len;
	char	*var;

	i = check_naming_convention(arg);
	if (i == 0)
	{
		var = malloc(sizeof(char) * ft_strlen(arg) - 1);
		if (var == NULL)
			return (NULL);
		(*index)++;
		ft_strlcpy(var, &arg[*index], ft_strlen(arg));
		return (var);
	}
	var = malloc(sizeof(char) * (i + 1));
	if (var == NULL)
		return (NULL);
	ft_strlcpy(var, arg, (i + 1));
	*index += i;
	return (var);
}
