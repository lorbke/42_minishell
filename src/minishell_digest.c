/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 15:51:43 by lorbke           ###   ########.fr       */
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

#define STR_SYNTAXERR ": syntax error near unexpected token `"

static void	print_syntax_error(int desc, char *error_loc)
{
	if (!desc && !error_loc)
		printf("%s: syntax error: unexpected end of file\n", SHELL_NAME);
	else if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "(");
	else
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, error_loc);
}

static bool	is_incomplete_input(t_stack *tokstack)
{
	while (tokstack && tokstack->next)
		tokstack = tokstack->next;
	if (tokstack && tokstack->token->desc == TOK_PIPE
		|| tokstack && tokstack->token->desc == TOK_AND
		|| tokstack && tokstack->token->desc == TOK_OR)
		return (1);
	return (0);
}

static t_ast	*parse_and_check_syntax(t_stack *tokstack)
{
	t_ast	*ast;

	ast = parser_tokstack_to_ast(&tokstack);
	if (ast)
		gc_add_garbage(ast, &parser_free_ast);
	if (tokstack)
	{
		exit_status_set(ERR_SYNTAXERR);
		print_syntax_error(tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	return (ast);
}

char	*digest_input_helper(char *input, int fd_in, int fd_out)
{
	t_stack	*tokstack;
	t_ast	*ast;
	int		exit_status;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	gc_add_garbage(tokstack, &lexer_free_tokstack);
	debug_lexer(tokstack);
	ast = parse_and_check_syntax(tokstack);
	if (!ast)
		return (input);
	debug_parser(ast, NULL);
	input = doccer_interpret_docs(tokstack, input);
	if (exit_status_get() != ERR_SUCCESS)
		return (input);
	debug_lexer(tokstack);
	if (is_incomplete_input(tokstack) == true)
	{
		exit_status_set(ERR_SYNTAXERR);
		print_syntax_error(0, NULL);
		return (input);
	}
	ast = parse_and_check_syntax(tokstack);
	if (!ast)
		return (input);
	debug_parser(ast, NULL);
	mssignal_change_mode(MSSIG_EXEC);
	exit_status_set(executer_exec_ast(ast, fd_in, fd_out));
	mssignal_change_mode(MSSIG_INTER);
	return (input);
}

char	*digest_input(char *input, int fd_in, int fd_out)
{
	char	*final;

	final = digest_input_helper(input, fd_in, fd_out);
	gc_free_all_garbage();
	return (final);
}
