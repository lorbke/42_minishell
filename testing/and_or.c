/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:43:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 15:49:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_pipe;

	if (!*tokstack
		|| ((*tokstack)->token->desc != TOK_AND
			&& (*tokstack)->token->desc != TOK_OR))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_pipeline(tokstack);
	if (!head->right)
		return (head);
	next_pipe = get_right(tokstack);
	if (!next_pipe)
		return (head);
	head = left_append_ast(next_pipe, head);
	return (head);
}

t_ast	*rule_and_or(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*new;

	left = rule_pipeline(tokstack);
	if (!left)
		return (NULL);
	if (!*tokstack
		|| ((*tokstack)->token->desc != TOK_AND
			&& (*tokstack)->token->desc != TOK_OR))
		return (left);
	right = get_right(tokstack);
	if (!right)
		return (left);
	right = left_append_ast(right, left);
	return (right);
}
