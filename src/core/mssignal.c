/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mssignal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:35 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:22:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h" // EXEC_* defines
#include "mssignal.h" // SIGNAL_* defines
#include "garbage_collector.h" // gc_free_all_garbage
#include "env.h" // g_sym_table
#include "utils.h" // env_free_sym_tab
#include "get_next_line.h" // get_next_line
#include <signal.h> // signal
#include <termios.h> // termios functions and struct
#include <stdio.h> // FILE type
#include <readline/readline.h> // readline functions
#include <unistd.h> // write
#include <stdlib.h> // exit
#include <stdbool.h> // bool

/* This is bad practice, calling readline functions inside a signal handler
can cause undefined behavior (see signal-safety).
Unfortunately, the 42_minishell subject does not allow another solution. */
/**
 * It handles the Ctrl+C signal
 * when the shell is in interactive mode
 * 
 * @param unused This is a GCC attribute that tells the compiler 
 * that the parameter is unused
 */
static void	handle_ctrlc_interactive(__attribute__((unused)) int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * It handles the Ctrl+C
 * signal by freeing all the memory allocated by the program, exiting 
 * the program and printing an error message
 * 
 * @param unused This is a GCC attribute that tells the compiler 
 * that the parameter is unused
 */
static void	handle_ctrlc_doc(__attribute__((unused)) int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	gc_free_all_garbage();
	env_free_sym_tab(g_sym_table);
	get_next_line(GNL_ERR);
	mssignal_change_mode(MSSIG_NINTER);
	exit(ERR_GENERAL);
}

/**
 * It sets the terminal to echo control characters or not
 * 
 * @param interactive If true, the function will disable the echo of 
 * control characters.
 * 
 * @return The return value of the function.
 */
static int	set_termios(bool interactive)
{
	struct termios	term_set;

	if (tcgetattr(STDIN_FILENO, &term_set) == RETURN_ERROR)
		return (EXIT_FAILURE);
	if (interactive)
		term_set.c_lflag &= ~ECHOCTL;
	else
		term_set.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_set) == RETURN_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * It sets the terminal to
 * canonical mode (line buffered) or non-canonical mode (character buffered)
 * depending on the value of the parameter
 * 
 * @param mode The mode to change to.
 */
void	mssignal_change_mode(char mode)
{
	if (mode == MSSIG_NINTER)
	{
		set_termios(false);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (mode == MSSIG_INTER)
	{
		set_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_ctrlc_interactive);
	}
	else if (mode == MSSIG_DOC)
	{
		set_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handle_ctrlc_doc);
	}
	else if (mode == MSSIG_EXEC)
	{
		set_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
