/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:37:35 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/12 15:21:52 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* This is bad practice, calling readline functions inside a signal handler
can cause undefined behavior (see signal-safety). 
Unfortunately, the 42_minishell subject does not allow another solution. */
static void	handle_ctrlc(int signal)
{
	write(STDOUT_FILENO, "\n", 1); 	// will print a new line, so readline will start a new line
	rl_on_new_line(); // will move the cursor to the beginning of the line
	rl_replace_line("", 0); // will replace the line buffer with nothing, but won't change what's on the terminal
	rl_redisplay(); // will display the line buffer on the terminal
	return ;
}

void	ms_init_signals(void)
{
	signal(SIGINT, handle_ctrlc);
	signal(SIGQUIT, SIG_IGN); // ignore ctrl+backslash
}
