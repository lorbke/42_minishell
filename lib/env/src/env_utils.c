/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:20:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 18:49:28 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, NULL, ft_strchr, ft_strdup, ft_strncmp
#include "env_private.h" // get_list_len
#include <stdbool.h> // bool
#include "libft.h" // ft_strncmp

static int	check_value(t_sym_tab *node);

char	**create_env_list(t_sym_tab **head)
{
	int			i;
	int			len;
	t_sym_tab	*temp;
	char		**env_list;

	len = get_list_len(head);
	env_list = malloc(sizeof(char *) * (len + 1));
	if (env_list == NULL)
		return (NULL);
	temp = *head;
	i = 0;
	while (temp != NULL)
	{
		if (check_value(temp) == 0 || ft_strncmp(temp->var, "?=", 2) == 0)
			temp = temp->next;
		else
		{
			env_list[i] = ft_strdup(temp->var);
			temp = temp->next;
			i++;
		}
	}
	env_list[i] = NULL;
	return (env_list);
}

char	*get_value(char *var)
{
	char	*value;
	char	*ptr_to_value;

	ptr_to_value = ft_strchr(var, '=');
	if (ptr_to_value == NULL)
		return (NULL);
	value = malloc(sizeof(char) * (ft_strlen(ptr_to_value) + 1));
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, ptr_to_value + 1, ft_strlen(ptr_to_value + 1) + 1);
	return (value);
}

static int	check_value(t_sym_tab *node)
{
	if (node == NULL)
		return (0);
	if (ft_strchr(node->var, '='))
		return (1);
	else
		return (0);
}

bool	env_is_var_value(char *var, char *value)
{
	t_sym_tab	*temp;
	char		*temp_str;

	if (var == NULL || value == NULL)
		return (false);
	temp = *g_sym_table;
	while (temp != NULL)
	{
		temp_str = temp->var;
		if (temp_str && ft_strncmp(temp_str, var, ft_strlen(var)) == 0
			&& temp_str[ft_strlen(var)] == '=')
		{
			while (*temp_str && *temp_str != '=')
				temp_str++;
			if (*temp_str
				&& ft_strncmp(temp_str + 1, value, ft_strlen(value) + 1) == 0)
				return (true);
		}
		temp = temp->next;
	}
	return (false);
}
