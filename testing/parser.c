/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 18:25:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// due to easier usage and because the additional memory and run time are negligible, 
// the token stack will be represented by a token_list instead of just a string

// free the tokstack after parsing

static t_ast	*rule_comp_cmd(t_stack **tokstack)
{
	return (rule_simple_cmd(tokstack));
}

static t_ast	*rule_pipe_helper(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*new;

	if (!*tokstack || (*tokstack)->token->desc != TOK_PIPE)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_comp_cmd(tokstack);
	if (!head->right)
		return (head);
	new = rule_pipe_helper(tokstack);
	if (!new)
		return (head);
	new->left = head;
	head = new;
	return (head);
}

static t_ast	*rule_pipe(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;

	left = rule_comp_cmd(tokstack);
	if (!left)
		return (NULL);
	right = rule_pipe_helper(tokstack);
	if (!right)
		return (left);
	if (!right->right)
		return (NULL);
	right = append_ast(right, left);
	return (right);
}

t_ast	*parse(t_stack	*tokstack)
{
	t_ast	*ast;

	ast = rule_pipe(&tokstack);
	return (ast);
}
