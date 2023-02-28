/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mssignal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:35 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 19:33:34 by lorbke           ###   ########.fr       */
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
static void	handle_ctrlc_interactive(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_ctrlc_doc(void)
{
	write(STDOUT_FILENO, "\n", 1);
	gc_free_all_garbage();
	env_free_sym_tab(g_sym_table);
	get_next_line(GNL_ERR);
	mssignal_change_mode(MSSIG_NINTER);
	exit(ERR_GENERAL);
}

/* Initializes the terminal settings according to interactive parameter. */
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
