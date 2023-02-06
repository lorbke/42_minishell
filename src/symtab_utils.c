/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:03:21 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 09:23:11 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "symtab.h"
#include "libft.h"

int get_list_len(t_sym_tab **head)
{
	t_sym_tab	*temp;
	int			len;

	len = 0;
	temp = *head;
	while (temp != NULL) {
		len++;
		temp = temp->next;
	}
	return (len);
}

t_sym_tab	*get_last_node(t_sym_tab *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_to_back(t_sym_tab **lst, t_sym_tab *new_node)
{
	t_sym_tab	*temp;

	if (*lst != NULL)
	{
		temp = get_last_node(*lst);
		temp->next = new_node;
	}
	else
		*lst = new_node;
}

t_sym_tab	*copy_node(t_sym_tab *node)
{
	t_sym_tab	*new_node;

	new_node = (t_sym_tab *)malloc(sizeof(t_sym_tab));
	if (!new_node) {
		// @note need to handle this error properly
	}
	new_node->name = ft_strdup(node->name);
	if (node->value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(node->value);
	new_node->next = NULL;
	return (new_node);
}
