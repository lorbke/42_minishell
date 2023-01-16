/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:50 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 12:32:35 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*create_ast_node(t_token	*token)
{
	t_ast	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_ast));
	new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_ast	*append_ast(t_ast *main, t_ast *append)
{
	t_ast	*temp;

	if (!main)
		return (append);
	temp = main;
	while (temp->left)
		temp = temp->left;
	temp->left = append;
	return (main);
}
