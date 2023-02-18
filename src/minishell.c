/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/18 19:20:48 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include "env.h" // global_var
#include "builtins.h" // builtin_exit
#include "utils.h" // free_list
#include "get_next_line.h" // get_next_line
#include <termios.h> // termios functions and struct
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <stdbool.h> // bool

// free the ast and the tokstack
// test if all fds are closed

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
		// if (!line) // exit buildin will be added later
		// 	builtin_exit(NULL);
		// if (ft_strncmp(line, "exit", 5) == 0) // exit buildin will be added later
		// 	builtin_exit(NULL);
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
	char	*line;

	// init global var
	g_sym_table = init_sym_tab(envp);
	ms_init_signals();
	// check if stdin is a terminal
	if (isatty(STDIN_FILENO))
	{
		if (init_termios(true) == ERROR)
			return (EXIT_FAILURE);
		ms_rep_loop();
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		process_command(line);
		free(line);
		free_list(g_sym_table);
	}
	return (EXIT_SUCCESS);
}
