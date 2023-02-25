/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 00:15:54 by lorbke           ###   ########.fr       */
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

// @todo env -i ./minishell leaks?
// @todo << "lim' cat -> never ending doc
// @todo echo " EOF -> no syntax err, implement proper quote identification in quote doc

// @todo random syntax error at case <echo< -> check with valgrind?

// @todo noninteractive mode -c

// @todo bash invalid command -> syntax error printed twice

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
void	interactive_mode(void)
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
			line = ms_digest_input(line);
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
		line = ms_digest_input(line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_status	exit_status;

	g_sym_table = init_sym_tab(envp);
	init_exit_status(g_sym_table);
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		interactive_mode();
	else
		non_interactive_mode();
	exit_status = ms_exit_status_get();
	mssignal_change_mode(MSSIG_NINTER);
	env_free_sym_tab(g_sym_table);
	return (exit_status);
}
