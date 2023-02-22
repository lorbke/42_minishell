/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:20:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 18:43:30 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, NULL, ft_strchr
#include "env_private.h" // get_list_len

static int	check_value(t_sym_tab *node);

#include <stdio.h>
char **create_env_list(t_sym_tab **head)
{
	int			i;
	int			len;
	t_sym_tab	*temp;
	char		**env_list;

	if (*head == NULL)
		return (NULL);
	len = get_list_len(head);
	env_list = malloc(sizeof(char *) * (len + 1));
	if (env_list == NULL) {
		return (NULL);
	}
	temp = *head;
	i = 0;
	while (temp != NULL) {
		if (check_value(temp) == 0 || ft_strncmp(temp->var, "?=", 2) == 0)
			temp = temp->next;
		else
		{
			// @note is this dup necessary or not?
			env_list[i] = ft_strdup(temp->var);
			temp = temp->next;
			i++;
		}
	}
	env_list[i] = NULL;
	return (env_list);
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
