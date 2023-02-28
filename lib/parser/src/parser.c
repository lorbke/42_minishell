/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:18:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros

/**
 * The calling function passes the tokenstack down and gets a sub-ast as return,
 * which is then connected to the main ast. The tokenstack is passed by 
 * reference, so that global iteration is possible.
 * If a part of the token stack does not match the grammar, 
 * the parser will stop parsing and return the ast that was created so far.
 * 
 * The parser functions very closely resemble the BNF grammar to ensure 
 * readability and maintainability.
 * 
 * The token stack pointer will point to the first token that was not parsed,
 * which makes detection of syntax errors and their location easy.
 * 
 * @param tokstack a pointer to a pointer to a t_stack. This is the token 
 * stack.
 * 
 * @return The ast is being returned.
 */
t_ast	*parser_tokstack_to_ast(t_stack	**tokstack)
{
	t_ast	*ast;

	ast = rule_and_or(tokstack);
	return (ast);
}
