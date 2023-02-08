/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:20:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/08 08:54:42 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_private.h"


//@note possible that we need this in other functions as well?
// static char *ft_strncpy(char *dest, const char *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < n && src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	while (i < n)
// 		dest[i++] = '\0';
// 	return dest;
// }

// void	split_env_var(char *env_var, char **name, char** value)
// {
// 	int	name_len;
// 	int	value_len;

// 	name_len = 0;
// 	if (!env_var) {
// 		// @note need to handle this error properly
// 	}
// 	while (env_var[name_len++] != '=');
// 	*name = malloc(sizeof(char) * name_len);
// 	if (name == NULL) {
// 		// @note need to handle this error properly
// 	}
// 	*name = ft_strncpy(*name, env_var, name_len - 1);
// 	value_len = ft_strlen(&env_var[name_len]);
// 	*value = malloc(sizeof(char) * (value_len + 1));
// 	if (value == NULL) {
// 		// @note need to handle this error properly
// 	}
// 	*value = ft_strncpy(*value, &env_var[name_len], value_len);
// }

int	check_value(t_sym_tab *node)
{
	if (!node)
		return (0);
	if (ft_strchr(node->var, '='))
		return (1);
	else
		return (0);
}

//@note you are mallocing the env list here
// possible that this will cause leaks when called with execve?
// or does it free this automatically?

#include <stdio.h>
char **create_env_list(t_sym_tab **head)
{
	int			i;
	int			len;
	t_sym_tab	*temp;
	char		**env_list;

	//@note check if it is possible to do it this way, without malloc
	len = get_list_len(head);
	env_list = malloc(sizeof(char *) * (len + 1));
	if (env_list == NULL) {
		// @note need to handle this error properly
	}
	temp = *head;
	i = 0;
	while (temp) {
		if (!check_value(temp))
			temp = temp->next;
		else
		{
			env_list[i] = temp->var;
			temp = temp->next;
			i++;
		}
	}
	return (env_list);
}
