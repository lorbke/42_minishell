/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:47:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:22:57 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, ft_isalpha, ft_isalnum, ft_strlen, ft_strncmp, ft_strchr
#include "expander_private.h" // ft_realloc

static int	get_var_len(char *var);

char	*get_var(char *arg, int *index)
{
	int		i;
	int		len;
	char	*var;

	i = 0;
	if (arg[i] && (ft_isalpha(arg[i]) || arg[i] == '_'))
	{
		while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
			i++;
	}
	if (i == 0)
		return (NULL);
	var = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var, arg,  (i + 1));
	*index += i;
	return (var);
}

char	*expand_var(char *arg)
{
	int			len;
	t_sym_tab	*temp;
	char		*value;

	temp = *g_sym_table;
	value = NULL;
	while (temp)
	{
		if (ft_strlen(arg) > get_var_len(temp->var))
			len = ft_strlen(arg);
		else
			len = get_var_len(temp->var);
		if (ft_strncmp(arg, temp->var, len) == 0)
		{
			value = ft_strdup(ft_strchr(temp->var, '=') + 1);
			break ;
		}
		temp = temp->next;
	}
	return (value);
}

char	*add_expanded_var(char *result, char *var, int *result_index)
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

static int	get_var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
