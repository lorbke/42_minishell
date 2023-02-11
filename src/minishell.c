/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/11 16:44:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "mssignal.h" // init_signals
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
// @todo rethink function names in minishell.h
// @todo exit status handling
// @todo error protections (malloc, open, etc.)
// @todo fix bug: overwriting first input when term window is exceeded

t_ast	*input_to_ast(char *input)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	ast = parser_tokstack_to_ast(&tokstack, SHELL_NAME);
	debug_parser(ast, tokstack);
	if (tokstack)
		return (NULL);
	return (ast);
}

char	process_input(char *input, int fd_in, int fd_out)
{
	char	exit_status;
	t_ast	*ast;

	ast = input_to_ast(input);
	if (!ast)
		return (EXEC_SYNTAXERR);
	exit_status = executer_exec_ast(ast, fd_in, fd_out);
	printf("-----exit status: %d\n", (int)exit_status);
	return (exit_status);
}

/* Read-Eval-Print-Loop. */
void	rep_loop(void)
{
	char	*line;

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

/* Initializes the terminal settings according to mode. */
static int	init_termios(bool mode)
{
	struct termios	term_set;

	if (tcgetattr(STDIN_FILENO, &term_set) == -1)
		return (EXIT_FAILURE);
	if (mode)
		term_set.c_lflag &= ~ECHOCTL; // this will prevent ^C from being printed (bitwise NOT)
	else
		term_set.c_lflag |= ECHOCTL; // restore ^C printing
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_set) == -1) // TCSANOW: change attributes immediately
		return (EXIT_FAILURE);
	debug_print_termios(&term_set);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (init_termios(true) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mssignal_change_mode(MSSIG_STD);
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		rep_loop();
	// else put input directly from STDIN to parser, executer etc
	return (EXIT_SUCCESS);
}
