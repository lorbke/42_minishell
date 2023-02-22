/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 21:41:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros"
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "garbage_collector.h" // gc_add_garbage
#include "libft.h" // ft_strncmp
#include "env.h" // global_var, init_exit_status, init_sym_tab
#include "builtins.h" // builtin_exit
#include "utils.h" // free_list
#include "get_next_line.h" // get_next_line
#include <termios.h> // termios functions and struct
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <fcntl.h> // STD*_FILENO defines
#include <stdbool.h> // bool

// @todo test if all fds are closed
// @todo exit behaviour: print exit when ctrl+d is pressed (is that handled in exit builtin?)
// @todo documentation with some kind of tool
// @todo improve the debugger
// @todo exit status handling
// @todo error protections (malloc, open, etc.)
// @todo fix bug: overwriting first input when term window is exceeded
// @todo turn on wall werror wextra in every makefile
// @todo heredoc and doc read switch to get_next_line?
// @todo add g_sym_table to garbage collector

// @todo env -i ./minishell segfaults
// @todo << "lim" -> no expansion
// @todo expansion in heredoc and infiles, except if lim in quotes
// @todo heredoc lim itself is not expanded
// @todo cat | cat | invalidcmd -> piping wrong

// @todo noninteractive mode -c

static bool	is_empty_str(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}

/* Read-Eval-Print-Loop. */
void	rep_loop(void)
{
	char	*line;

	mssignal_change_mode(MSSIG_INTER);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			builtin_exit_b(NULL);
		if (*line)
		{
			line = ms_digest_input(line, STDIN_FILENO, STDOUT_FILENO);
			if (!is_empty_str(line))
				add_history(line);
		}
		free(line);
	}
	rl_clear_history();
}

void	non_interactive_mode(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		line = ms_digest_input(line, STDIN_FILENO, STDOUT_FILENO);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_sym_table = init_sym_tab(envp);
	init_exit_status(g_sym_table);
	// gc_add_garbage(g_sym_table, &free_list);
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		rep_loop();
	else
	{
		non_interactive_mode();
		// @note replace by gc later on?
		free_list(g_sym_table);
	}
	// else put input directly from STDIN to parser, executer etc
	mssignal_change_mode(MSSIG_NINTER);
	return (EXIT_SUCCESS);
}
