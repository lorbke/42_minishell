/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:43:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 18:44:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*rule_and_or(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*new;

	left = rule_pipeline(tokstack);
	if (!left)
		return (NULL);
	if (!*tokstack || ((*tokstack)->token->desc != TOK_AND && (*tokstack)->token->desc != TOK_OR))
		return (left);
	right = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	right->left = left;
	right->right = rule_pipeline(tokstack);
	if (!right->right)
		return (NULL);
	new = rule_and_or(tokstack);
	if (!new)
		return (right);
	new->left = right;
	right = new;
	return (right);
}
