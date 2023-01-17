/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:38:26 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 15:41:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_pipe;

	if (!*tokstack || (*tokstack)->token->desc != TOK_PIPE)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_comp_cmd(tokstack);
	if (!head->right)
		return (head);
	next_pipe = get_right(tokstack);
	if (!next_pipe)
		return (head);
	head = left_append_ast(next_pipe, head);
	return (head);
}

t_ast	*rule_pipeline(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;

	left = rule_comp_cmd(tokstack);
	if (!left)
		return (NULL);
	right = get_right(tokstack);
	if (!right)
		return (left);
	right = left_append_ast(right, left);
	return (right);
}
