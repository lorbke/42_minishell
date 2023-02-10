/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:35 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/10 18:12:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h" // EXEC_* defines
#include "mssignal.h" // SIGNAL_* defines
#include <signal.h> // signal
#include <stdio.h> // FILE type
#include <readline/readline.h> // readline functions
#include <unistd.h> // write
#include <stdlib.h> // exit

/* This is bad practice, calling readline functions inside a signal handler
can cause undefined behavior (see signal-safety). 
Unfortunately, the 42_minishell subject does not allow another solution. */
static void	handle_ctrlc(int signal)
{
	write(STDOUT_FILENO, "\n", 1); 	// will print a new line, so readline will start a new line
	rl_on_new_line(); // will move the cursor to the beginning of the line
	rl_replace_line("", 0); // will replace the line buffer with nothing, but won't change what's on the terminal
	rl_redisplay(); // will display the line buffer on the terminal
}

static void	handle_ctrlc_heredoc(int signal)
{
	exit(EXEC_GENERALERR);
}

static void	handle_ctrlc_notheredoc(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
}

void	mssignal_change_mode(char mode)
{
	signal(SIGQUIT, SIG_IGN); // ignore ctrl+backslash
	if (mode == MSSIG_STD)
		signal(SIGINT, handle_ctrlc);
	else if (mode == MSSIG_NHDOC)
		signal(SIGINT, handle_ctrlc_notheredoc);
	else
		signal(SIGINT, handle_ctrlc_heredoc);
}
