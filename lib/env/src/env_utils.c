/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:20:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 14:17:09 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_private.h"

static char *ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return dest;
}

void	split_env_var(char *env_var, char **name, char** value)
{
	int	name_len;
	int	value_len;

	name_len = 0;
	if (!env_var) {
		// @note need to handle this error properly
	}
	while (env_var[name_len++] != '=');
	*name = malloc(sizeof(char) * name_len);
	if (name == NULL) {
		// @note need to handle this error properly
	}
	*name = ft_strncpy(*name, env_var, name_len - 1);
	value_len = ft_strlen(&env_var[name_len]);
	*value = malloc(sizeof(char) * (value_len + 1));
	if (value == NULL) {
		// @note need to handle this error properly
	}
	*value = ft_strncpy(*value, &env_var[name_len], value_len);
}

char **create_env_list(t_sym_tab **head)
{
	int			i;
	int			len;
	t_sym_tab	*temp;
	char		**env_list;

	len = get_list_len(head);
	env_list = malloc(sizeof(char *) * (len + 1));
	if (env_list == NULL) {
		// @note need to handle this error properly
	}
	temp = *head;
	i = 0;
	while (temp) {
		if (temp->value == NULL)
			temp = temp->next;
		else
		{
			env_list[i] = ft_strjoin(temp->name, "=");
			env_list[i] = ft_strjoin(env_list[i], temp->value);
			temp = temp->next;
			i++;
		}
	}
	return (env_list);
}
