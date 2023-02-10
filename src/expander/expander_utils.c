/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:47:22 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/10 08:52:42 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // malloc, ft_isalpha, ft_isalnum, ft_strlen, ft_strncmp, ft_strchr
#include "expander_private.h" // ft_realloc

static int	get_var_len(char *var);

char	*get_var(char *arg, int *index)
{
	int		i;
	char	*var;

	i = 0;
	while (arg[i] && ft_isalpha(arg[i]) || arg[i] == '_')
		i++;
	if (i == 0)
		return (NULL);
	var = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (arg[i] && ft_isalnum(arg[i]) || arg[i] == '_')
	{
		var[i] = arg[i];
		i++;
	}
	var[i] = '\0';
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
			value = ft_strchr(temp->var, '=') + 1;
			break ;
		}
		temp = temp->next;
	}
	return (value);
}

char	*add_expanded_var(char *result, char *var, int *index)
{
	int		i;
	int		len;
	char	*arg;

	i = 0;
	len = 0;
	if (!result)
		arg = malloc(sizeof(char) * (ft_strlen(var) + 1));
	else
	{
		arg = ft_realloc(result, ft_strlen(result) + ft_strlen(var));
		len = ft_strlen(arg);
	}
	while (var[i])
		arg[len++] = var[i++];
	arg[len] = '\0';
	*index = ft_strlen(var);
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
