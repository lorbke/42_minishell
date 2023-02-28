/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:38:26 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/01 00:45:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL

/**
 * It takes a pointer to a pointer to a stack of tokens, and returns 
 * a pointer to an AST node
 * 
 * @param tokstack a pointer to a pointer to a token stack.
 * 
 * @return The right side of the pipe.
 */
static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_pipe;

	if (!*tokstack || (*tokstack)->token->desc != TOK_PIPE)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	if (!(*tokstack)->next)
		return (head);
	*tokstack = (*tokstack)->next;
	head->right = rule_simple_cmd(tokstack);
	if (!head->right)
		return (NULL);
	next_pipe = get_right(tokstack);
	if (!next_pipe)
		return (head);
	head = append_left_ast(next_pipe, head);
	return (head);
}

/**
 * It creates a pipeline.
 * 
 * @param tokstack The token stack.
 * 
 * @return The left and right nodes of the tree.
 */
t_ast	*rule_pipeline(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;

	left = rule_simple_cmd(tokstack);
	if (!left)
		return (NULL);
	right = get_right(tokstack);
	if (!right)
		return (left);
	right = append_left_ast(right, left);
	return (right);
}
