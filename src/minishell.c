/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 14:25:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include <termios.h> // termios functions and struct
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <stdbool.h> // bool

// @todo free the ast and the tokstack
// @todo test if all fds are closed
// @todo exit behaviour: print exit when ctrl+d is pressed (is that handled in exit builtin?)
// @todo documentation with some kind of tool
// @todo improve the debugger

char	process_input(char *input)
{
	t_stack	*tokstack;
	t_ast	*ast;
	char	exit_status;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	ast = parser_tokstack_to_ast(&tokstack);
	debug_parser(ast, tokstack);
	if (tokstack)
	{
		// @note ugly edge case, maybe just remove it?
		if (tokstack->token->desc == TOK_REDIR_IN
			|| tokstack->token->desc == TOK_REDIR_OUT
			|| tokstack->token->desc == TOK_REDIR_APPEND
			|| tokstack->token->desc == TOK_REDIR_HEREDOC)
			printf("%s: syntax error near unexpected token `%s'\n",
				SHELL_NAME, "newline");
		else
			printf("%s: syntax error near unexpected token `%s'\n",
				SHELL_NAME, tokstack->token->word);
		return (2);
	}
	exit_status = executer_exec_ast(&ast);
	print_exec_error(exit_status, ast->token->word);
	return (exit_status);
}

/* Read-Eval-Print-Loop. */
void	ms_rep_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line) // exit buildin will be added later
			break ;
		if (ft_strncmp(line, "exit", 5) == 0) // exit buildin will be added later
			break ;
		if (*line)
		{
			add_history(line);
			process_input(line);
		}
		free(line);
	}
	rl_clear_history();
}

/* Initializes the terminal settings according to mode. */
static int	init_termios(bool mode)
{
	struct termios	term_set;

	if (tcgetattr(STDIN_FILENO, &term_set) == -1)
		return (ERROR);
	if (mode)
		term_set.c_lflag &= ~ECHOCTL; // this will prevent ^C from being printed (bitwise NOT)
	else
		term_set.c_lflag |= ECHOCTL; // restore ^C printing
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_set) == -1) // TCSANOW: change attributes immediately
		return (ERROR);
	debug_print_termios(&term_set);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (init_termios(true) == ERROR)
		return (EXIT_FAILURE);
	ms_init_signals();
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		ms_rep_loop();
	// else put input directly from STDIN to parser, executer etc
	return (EXIT_SUCCESS);
}
