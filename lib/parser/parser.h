/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/18 15:57:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is a recursive descent (RD) parser, as opposed to original bash's yacc
look-ahead left-to-right (LALR) parser. The RD parser was chosen because it
is a solution that is more interesting to me and because the current
implementation of the bash parser seems to be a relict of the past and even
bash's maintainers argue that it has weaknesses. */

/* The parser follows the following Backus-Naur-Form (BNF) grammar:
	<all>        ::=  <and_or> <newline>
	<and_or>     ::=  <pipeline> { ('&&' | '||') <pipeline> }
	<pipeline>   ::=  <command> { '|' <command> }
	<comp_cmd>   ::=  ( <simple_cmd> | <and_or> )
	<simple_cmd> ::=  { ( <redirect> | <word> ) }
	<redirect>   ::=  ( '<' | '>' | '<<' | '>>' ) <word>
	<word>       ::=  ( any character except certain special characters )
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

t_ast	*parser_tokstack_to_ast(t_stack	**tokstack);

#endif
