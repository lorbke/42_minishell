/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_symtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:00:37 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 20:36:04 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "env_private.h"
#include <stdlib.h>
#include <stdio.h>

t_sym_tab	*new_sym_tab_node(char *var);

t_sym_tab	**init_sym_tab(char **envp)
{
	t_sym_tab	**head;
	char		*var;

	head = malloc(sizeof(t_sym_tab));
	if (head == NULL)
		return (NULL);
	if (envp[0] == NULL)
	{
		*head = NULL;
		return (head);
	}
	while (*envp != NULL)
	{
		var = ft_strdup(*envp);
		add_to_back(head, new_sym_tab_node(var));
		free(var);
		envp++;
	}
	return (head);
}

t_sym_tab	*new_sym_tab_node(char *var)
{
	t_sym_tab	*node;

	node = malloc(sizeof(t_sym_tab));
	if (node == NULL)
		return (NULL);
	if (var == NULL)
		node->var = NULL;
	else
		node->var = ft_strdup(var);
	node->next = NULL;
	return (node);
}

void	init_exit_status(t_sym_tab **head)
{
	t_sym_tab	*node;
	char		*var;

	var = malloc(sizeof(char) * 6);
	if (var == NULL)
		return ;
	ft_strlcpy(var, "?=0", 6);
	node = new_sym_tab_node(var);
	add_to_back(head, node);
}
