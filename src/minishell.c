/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/20 17:37:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include "env.h" // global_var
#include <termios.h> // termios functions and struct
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <stdbool.h> // bool

// free the ast and the tokstack
// test if all fds are closed

// global var
t_sym_tab **g_sym_table;

void	process_command(char *command)
{
	t_stack	*tokstack;
	t_ast	*ast;
	int		i;

	tokstack = lexer_str_to_tokstack(command, CMD_SEPS, CMD_ESCS);
	debug_lexer(tokstack);
	if (tokstack)
	{
		ast = parser_tokstack_to_ast(&tokstack);
		debug_parser(ast, tokstack);
		if (ast)
		{
			executer_exec_ast(ast);
		}
	}
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
			process_command(line);
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
	// init global var
	g_sym_table = init_sym_tab(envp);
	if (init_termios(true) == ERROR)
		return (EXIT_FAILURE);
	ms_init_signals();
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		ms_rep_loop();
	// else put input directly from STDIN to parser, executer etc
	return (EXIT_SUCCESS);
}
