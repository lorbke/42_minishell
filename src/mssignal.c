/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mssignal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:35 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/24 20:56:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h" // EXEC_* defines
#include "mssignal.h" // SIGNAL_* defines
#include "garbage_collector.h" // gc_free_all_garbage
#include "env.h" // g_sym_table
#include "utils.h" // env_free_sym_tab
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
static void	handle_ctrlc_interactive(int signal)
{
	write(STDOUT_FILENO, "\n", 1); 	// will print a new line, so readline will start a new line
	rl_on_new_line(); // will move the cursor to the beginning of the line
	rl_replace_line("", 0); // will replace the line buffer with nothing, but won't change what's on the terminal
	rl_redisplay();  // will display the line buffer on the terminal
}

static void	handle_ctrlc_doc(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	gc_free_all_garbage();
	env_free_sym_tab(g_sym_table);
	exit(ERR_GENERAL);
}

// /* Because of the way bash handles ^C, 
// a new line needs to be printed when a command is interrupted. */
// static void	handle_ctrlc_exec(int signal)
// {
// 	write(STDOUT_FILENO, "\n", 1);
// }

/* Initializes the terminal settings according to interactive parameter. */
static int	set_termios(bool interactive)
{
	struct termios	term_set;

	if (tcgetattr(STDIN_FILENO, &term_set) == -1)
		return (EXIT_FAILURE);
	if (interactive)
		term_set.c_lflag &= ~ECHOCTL; // this will prevent ^C from being printed (bitwise NOT)
	else
		term_set.c_lflag |= ECHOCTL; // restore ^C printing
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_set) == -1) // TCSANOW: change attributes immediately
		return (EXIT_FAILURE);
	return (0);
}

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
		signal(SIGINT, handle_ctrlc_interactive);
	}
	else if (mode == MSSIG_DOC)
	{
		set_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrlc_doc);
	}
	else if (mode == MSSIG_EXEC)
	{
		set_termios(true);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}
