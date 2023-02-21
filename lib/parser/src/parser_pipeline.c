/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:38:26 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 17:59:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL

static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_pipe;

	if (!*tokstack || (*tokstack)->token->desc != TOK_PIPE)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_simple_cmd(tokstack);
	if (!head->right)
	{
		head->right = create_ast_node(create_token_empty());
		return (head);
	}
	next_pipe = get_right(tokstack);
	if (!next_pipe)
		return (head);
	head = append_left_ast(next_pipe, head);
	return (head);
}

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
