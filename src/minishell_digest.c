/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 20:44:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // defines
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack, lexer_free_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include "garbage_collector.h" // gc_add_garbage etc.
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <stdbool.h> // bool

static bool	is_input_incomplete(t_stack *tokstack)
{
	while (tokstack && tokstack->next)
		tokstack = tokstack->next;
	if (tokstack && (tokstack->token->desc == TOK_PIPE
			|| tokstack->token->desc == TOK_AND
			|| tokstack->token->desc == TOK_OR
			|| tokstack->token->word && tokstack->token->word[0] == ')'))
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_error(ms_exit_status_get(),
			tokstack->token->desc, tokstack->token->word);
		return (true);
	}
	return (false);
}

static t_ast	*parse_and_check_syntax(t_stack *tokstack)
{
	t_ast	*ast;

	ast = parser_tokstack_to_ast(&tokstack);
	if (ast)
		gc_add_garbage(ast, &parser_free_ast);
	if (tokstack)
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_error(ms_exit_status_get(),
			tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	return (ast);
}

char	*digest_input_helper(char *input, int fd_in, int fd_out)
{
	t_stack	*tokstack;
	t_ast	*ast;
	int		exit_status;

	tokstack = lexer_str_to_tokstack(input);
	if (!tokstack)
		return (input);
	debug_lexer(tokstack);
	gc_add_garbage(tokstack, &lexer_free_tokstack);
	ast = parse_and_check_syntax(tokstack);
	if (!ast)
		return (input);
	debug_parser(ast, NULL);
	input = doccer_interpret_docs(tokstack, input);
	if (ms_exit_status_get() != ERR_SUCCESS)
		return (input);
	debug_lexer(tokstack);
	if (is_input_incomplete(tokstack) == true)
		return (input);
	ast = parse_and_check_syntax(tokstack);
	if (!ast)
		return (input);
	debug_parser(ast, NULL);
	mssignal_change_mode(MSSIG_EXEC);
	ms_exit_status_set(executer_exec_ast(ast, fd_in, fd_out));
	mssignal_change_mode(MSSIG_INTER);
	return (input);
}

char	*ms_digest_input(char *input, int fd_in, int fd_out)
{
	char	*final;

	final = digest_input_helper(input, fd_in, fd_out);
	gc_free_all_garbage();
	return (final);
}
