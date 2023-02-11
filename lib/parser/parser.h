/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/11 12:25:58 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is a recursive descent (RD) parser, as opposed to original bash's yacc
look-ahead left-to-right (LALR) parser. The RD parser was chosen because it
is a solution that is more interesting to me and because the current
implementation of the bash parser seems to be a relict of the past and even
bash's maintainers argue that it has weaknesses. */

/* The parser takes a stack of tokens (t_stack) as a parameter and converts it
to an abstract syntax tree (t_ast) according to the following

Backus-Naur-Form (BNF) grammar:
	<all>        ::=  <and_or> <newline>
	<and_or>     ::=  <pipeline> { ('&&' | '||') <pipeline> }
	<pipeline>   ::=  <command> { '|' <command> }
	<comp_cmd>   ::=  ( <simple_cmd> | <and_or> )
	<simple_cmd> ::=  { ( <redirect> | <word> ) }
	<redirect>   ::=  ( '<' | '>' | '<<' | '>>' ) <word>
	<word>       ::=  ( any character except certain special characters )

If a part of the token stack does not match the grammar, the parser will stop parsing
and return the ast that was created so far.
The token stack pointer will point to the first token that was not parsed.
*/

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h" // t_token, t_stack

typedef struct s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_ast	*parser_tokstack_to_ast(t_stack	**tokstack, char *error_name);

#endif
