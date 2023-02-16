/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:43:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 14:46:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL

static t_ast	*get_right(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*next_andor;

	if (!*tokstack
		|| ((*tokstack)->token->desc != TOK_AND
			&& (*tokstack)->token->desc != TOK_OR))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_pipeline(tokstack);
	if (!head->right)
	{
		head->right = create_ast_node(create_token_unclosed());
		return (head);
	}
	next_andor = get_right(tokstack);
	if (!next_andor)
		return (head);
	head = append_left_ast(next_andor, head);
	return (head);
}

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
