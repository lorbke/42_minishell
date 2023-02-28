/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:43:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 20:47:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL

/**
 * It takes a stack of tokens,
 * and returns an AST node representing the right side of a logical AND or OR
 * operator
 * 
 * @param tokstack a pointer to a pointer to a token stack.
 * 
 * @return The head of the ast.
 */
static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_andor;

	if (!*tokstack
		|| ((*tokstack)->token->desc != TOK_AND
			&& (*tokstack)->token->desc != TOK_OR))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	head->right = rule_pipeline(&(*tokstack)->next);
	if (!head->right)
		return (NULL);
	*tokstack = (*tokstack)->next;
	next_andor = get_right(tokstack);
	if (!next_andor)
		return (head);
	head = append_left_ast(next_andor, head);
	return (head);
}

/**
 * It takes a token stack,
 * creates an AST node from the top of the stack, and then checks if there's
 * another token on the stack. If there is, it creates another AST node from the
 * top of the stack, and then appends the first AST node to the second
 * 
 * @param tokstack The token stack.
 * 
 * @return The left and right nodes of the tree.
 */
t_ast	*rule_and_or(t_stack **tokstack)
{
	t_ast	*left;
	t_ast	*right;

	left = rule_pipeline(tokstack);
	if (!left)
		return (NULL);
	right = get_right(tokstack);
	if (!right)
		return (left);
	right = append_left_ast(right, left);
	return (right);
}
