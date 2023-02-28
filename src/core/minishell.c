/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:21:03 by lorbke           ###   ########.fr       */
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

/**
 * It returns true if the string is empty, false otherwise
 * 
 * @param str The string to check.
 * 
 * @return The function is_empty_str() returns true if the string is empty,
 * false otherwise.
 */
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

/**
 * It reads a line from the user,
 * digests it, and then adds it to the history
 */
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
			gc_free_all_garbage();
			if (!is_empty_str(line))
				add_history(line);
		}
		free(line);
	}
	rl_clear_history();
}

/**
 * It reads a line from the standard input,
 * digests it, frees the memory allocated for the line,
 * and repeats the process until there's no more input
 */
void	non_interactive_mode(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		line = ms_digest_input(line);
		gc_free_all_garbage();
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

/**
 * It initializes the symbol table, then it calls either 
 * the interactive or non-interactive mode depending on whether 
 * the shell is running in a terminal or not
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @param envp The environment variables.
 * 
 * @return The exit status of the program.
 */
int	main(int argc, char **argv, char **envp)
{
	t_status	exit_status;

	(void)argc;
	(void)argv;
	g_sym_table = init_sym_tab(envp);
	init_exit_status(g_sym_table);
	if (isatty(STDIN_FILENO))
		interactive_mode();
	else
		non_interactive_mode();
	exit_status = ms_exit_status_get();
	mssignal_change_mode(MSSIG_NINTER);
	env_free_sym_tab(g_sym_table);
	return (exit_status);
}
