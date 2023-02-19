/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_digest.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:54:11 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // defines
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf

#define STR_SYNTAXERR ": syntax error near unexpected token `"

static void	print_syntax_error(int desc, char *error_loc)
{
	if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "(");
	else
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, error_loc);
}

// @todo new heredoc function
// @todo whole doccer error handling
char	*digest_input(char *input, int fd_in, int fd_out)
{
	t_stack	*tokstack;
	t_ast	*ast;
	int		exit_status;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	input = doccer_interpret_docs(tokstack, input);
	debug_lexer(tokstack);
	// syntax error
	ast = parser_tokstack_to_ast(&tokstack);
	debug_parser(ast, NULL);
	mssignal_change_mode(MSSIG_EXEC);
	exit_status = executer_exec_ast(ast, fd_in, fd_out);
	mssignal_change_mode(MSSIG_INTER);
	printf("-----exit status: %d\n", exit_status);
	return (input);
}
