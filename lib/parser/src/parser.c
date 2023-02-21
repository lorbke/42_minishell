/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 18:01:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // free
#include <stdio.h> // printf

// @note every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// @note due to easier usage and because the additional memory and run time are negligible, 
// @note the token stack will be represented by a token_list instead of just a string

// @note quote handling also probably incorrect

t_ast	*parser_tokstack_to_ast(t_stack	**tokstack)
{
	t_ast	*ast;

	ast = rule_and_or(tokstack);
	return (ast);
}
