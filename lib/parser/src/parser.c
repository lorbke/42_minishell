/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/12 18:17:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // free
#include <stdio.h> // printf

#define ERR_STR ": syntax error near unexpected token `"

// @note every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// @note due to easier usage and because the additional memory and run time are negligible, 
// @note the token stack will be represented by a token_list instead of just a string

// @todo rule_all was skipped
// @todo newline implementation still needed (case: < -> bash error is invalid token at newline)

// @note quote handling also probably incorrect
// @todo unclosed quote syntax error

static void	print_error(int desc, char *error_loc, char *error_name)
{
	// @note ugly edge case, maybe just remove it?
	if (desc == TOK_REDIR_IN
		|| desc == TOK_REDIR_OUT
		|| desc == TOK_REDIR_APPEND
		|| desc == TOK_REDIR_HEREDOC)
		printf("%s%s%s'\n",
			error_name, ERR_STR, "newline");
	else if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			error_name, ERR_STR, "(");
	else
		printf("%s%s%s'\n",
			error_name, ERR_STR, error_loc);
}

t_ast	*parser_tokstack_to_ast(t_stack	**tokstack, char *error_name)
{
	t_ast	*ast;

	ast = rule_and_or(tokstack);
	if (*tokstack)
		print_error((*tokstack)->token->desc, (*tokstack)->token->word, error_name);
	return (ast);
}
