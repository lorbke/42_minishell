/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/14 17:14:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history

// @todo free the ast and the tokstack
// @todo test if all fds are closed
// @todo exit behaviour: print exit when ctrl+d is pressed (is that handled in exit builtin?)
// @todo documentation with some kind of tool
// @todo improve the debugger
// @todo rethink function names in minishell.h
// @todo exit status handling
// @todo error protections (malloc, open, etc.)
// @todo fix bug: overwriting first input when term window is exceeded
// @todo is not a terminal case handling

#define STR_SYNTAXERR ": syntax error near unexpected token `"

static void	print_syntax_error(int desc, char *error_loc)
{
	if (desc == TOK_REDIR_IN
		|| desc == TOK_REDIR_OUT
		|| desc == TOK_REDIR_APPEND
		|| desc == TOK_REDIR_HEREDOC)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "newline");
	else if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "(");
	else
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, error_loc);
}

t_ast	*input_to_ast(char *input)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	ast = parser_tokstack_to_ast(&tokstack);
	debug_parser(ast, tokstack);
	if (tokstack)
	{
		print_syntax_error(tokstack->token->desc, tokstack->token->word);
		return (NULL);
	}
	return (ast);
}

t_status	process_input(char *input, int fd_in, int fd_out)
{
	t_status	exit_status;
	t_ast		*ast;

	ast = input_to_ast(input);
	if (!ast)
	{
		// printf("-----exit status: %d\n", EXEC_SYNTAXERR);
		return (EXEC_SYNTAXERR);
	}
	mssignal_change_mode(MSSIG_EXEC);
	exit_status = executer_exec_ast(ast, fd_in, fd_out);
	mssignal_change_mode(MSSIG_INTER);
	// printf("-----exit status: %d\n", exit_status);
	return (exit_status);
}

/* Read-Eval-Print-Loop. */
void	rep_loop(void)
{
	char	*line;

	mssignal_change_mode(MSSIG_INTER);
	while (1)
	{
		line = readline(PROMPT);
		if (!line || ft_strncmp(line, "exit", 5) == 0) // exit buildin will be added later
			break ;
		if (*line)
		{
			add_history(line);
			process_input(line, STDIN_FILENO, STDOUT_FILENO);
		}
		free(line);
	}
	rl_clear_history();
}

int	main(void)
{
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		rep_loop();
	// else put input directly from STDIN to parser, executer etc
	return (EXIT_SUCCESS);
}
