/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:47:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 19:18:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table, get_value
#include "libft.h" // NULL, malloc, free, ft_isalpha, ft_isalnum, ft_strlen,
// ft_strncmp, ft_strchr, ft_strlcat, ft_strlcpy
#include "../utils.h" // check_naming_convention, ft_realloc
#include "expander_private.h" // add_char_to_str

char	*tilde_expansion(char *result, char *arg, int *i, int *result_i)
{
	char	*home;
	char	*expanded_home;

	home = expand_var("HOME");
	if ((result || arg[*i + 1] != '/') && ft_strlen(arg) > 1)
		expanded_home = add_char_to_str(result, '~', &(*i), &(*result_i));
	else if (home != NULL)
	{
		expanded_home = add_expanded_var(result, home, &(*result_i));
		(*i)++;
	}
	else
		expanded_home = add_char_to_str(result, '~', &(*i), &(*result_i));
	return (expanded_home);
}

char	*add_expanded_var(char *result, char *var, int *result_i)
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
	*result_i = ft_strlen(arg);
	return (arg);
}

char	*get_var(char *arg, int *i)
{
	int		j;
	char	*var;

	j = check_naming_convention(arg);
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
				value = get_value(temp->var);
			else
				value = NULL;
			break ;
		}
		temp = temp->next;
	}
	return (value);
}
