/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:23:41 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/05 18:29:30 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtab.h"

void	builtin_unset(char *var, t_sym_tab **sym_table)
{
	remove_node(var, sym_table);
}

static void	remove_first_node(t_sym_tab	*first, t_sym_tab **head)
{
	t_sym_tab	*temp;

	temp = first->next;
	*head = temp;
	free(first->name);
	if (first->value)
		free(first->value);
	free(first);
}

static void	remove_node(char *var, t_sym_tab **head)
{
	t_sym_tab	*temp;
	t_sym_tab	*prev;

	prev = *head;
	temp = (*head)->next;
	if (ft_strncmp(prev->name, var, ft_strlen(var)) == 0)
	{
		remove_first_node(prev, head);
		return ;
	}
	while (temp)
	{
		if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0)
		{
			prev->next = temp->next;
			free(temp->name);
			if (temp->value)
				free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
