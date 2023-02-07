/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_symtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:00:37 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 14:26:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "env_private.h"
#include <stdlib.h>

t_sym_tab	**init_sym_tab(char **envp)
{
	t_sym_tab	**head;

	head = (t_sym_tab **)malloc(sizeof(t_sym_tab));
	while (*envp) {
		add_to_back(head, env_to_sym_tab_node(*envp));
		envp++;
	}
	return(head);
}

t_sym_tab	*env_to_sym_tab_node(char *env)
{
	t_sym_tab	*node;

	node = (t_sym_tab *)malloc(sizeof(t_sym_tab));
	if (node == NULL) {
		// @note need to handle this error properly
	}
	node->next = NULL;
	split_env_var(env, &node->name, &node->value);
	return (node);
}

t_sym_tab	*new_sym_tab_node(char *name, char *value)
{
	t_sym_tab	*node;

	node = (t_sym_tab *)malloc(sizeof(t_sym_tab));
	if (node == NULL) {
		// @note need to handle this error properly
	}
	node->name = ft_strdup(name);
	if (value == NULL)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}
