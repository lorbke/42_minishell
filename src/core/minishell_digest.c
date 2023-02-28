/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/01 00:46:19 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // defines
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack, lexer_free_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_get_complete_tokstack
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "garbage_collector.h" // gc_add_garbage etc.
#include <stdlib.h> // NULL

/**
 * It executes the AST
 * 
 * @param ast The abstract syntax tree to execute.
 */
static void	digest_execution(t_ast *ast)
{
	t_status	exit_status;

	debug_message("\n=========Execution=========\n", 0);
	mssignal_change_mode(MSSIG_EXEC);
	exit_status = executer_exec_ast(ast);
	ms_exit_status_set(exit_status);
	mssignal_change_mode(MSSIG_INTER);
	debug_message("===========================\n", 0);
}

/**
 * It takes a token stack,
 * converts it to an abstract syntax tree, and returns the abstract syntax tree
 * 
 * @param tokstack a pointer to a pointer to a token stack.
 * 
 * @return The ast is being returned.
 */
static t_ast	*digest_parsing(t_stack *tokstack)
{
	t_ast	*ast;

	ast = parser_tokstack_to_ast(&tokstack);
	if (ast)
		gc_add_garbage(ast, &parser_free_ast);
	debug_parser(ast);
	if (tokstack)
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_syntax_error(tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	return (ast);
}

/**
 * It takes a string,
 * and returns a stack of tokens
 * 
 * @param input a pointer to a string that contains the input to be parsed.
 * 
 * @return A pointer to a t_stack struct.
 */
static t_stack	*digest_lexing(char **input)
{
	t_stack		*tokstack;
	t_status	exit_status;

	exit_status = ERR_SUCCESS;
	tokstack = doccer_get_complete_tokstack(input, &exit_status);
	if (tokstack)
		gc_add_garbage(tokstack, &lexer_free_tokstack);
	debug_lexer(tokstack);
	if (exit_status != ERR_SUCCESS)
	{
		ms_exit_status_set(exit_status);
		return (NULL);
	}
	return (tokstack);
}

/**
 * It takes a string,
 * lexes it, parses it, and executes it
 * 
 * @param input The input string.
 * 
 * @return The input string.
 */
char	*ms_digest_input(char *input)
{
	t_stack		*tokstack;
	t_ast		*ast;

	tokstack = digest_lexing(&input);
	if (!tokstack)
		return (input);
	ast = digest_parsing(tokstack);
	if (!ast)
		return (input);
	digest_execution(ast);
	return (input);
}
