/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/09 23:46:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#define PROMPT "minishell> "
#define EXIT "exit"

/* Free this 
	free(line);
	rl_clear_history();
*/

// ^C is still printed on the terminal, this can be fixed by using termios (tcsetattr)
void	handle_ctrlc(int signal)
{
	// will print a new line, so readline will start a new line
	write(STDOUT_FILENO, "\n", 1);
	// will move the cursor to the beginning of the line
	rl_on_new_line();
	// will replace the line buffer with nothing, but won't change what's on the terminal
	rl_replace_line("", 0);
	// will display the line buffer on the terminal
	rl_redisplay();
	return ;
}

// ctrl + d (EOF) is not handled, this can be fixed by using termios (tcsetattr)
void	ms_init_signals(void)
{
	signal(SIGINT, handle_ctrlc);
}

// unclear if EXIT check is needed, or if this can be done with termios
/* Read-Eval-Print-Loop */
void	ms_rep_loop(void)
{
	char	*line;

	line = ft_calloc(LINE_MAX, sizeof(char));
	while (1)
	{
		line = readline(PROMPT);
		if (!*line)
			continue ;
		if (ft_strncmp(line, EXIT, sizeof(EXIT)) == 0)
			break ;
		add_history(line);
		write(1, "Input: ", 7);
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
	}
}

int	main(void)
{
	ms_init_signals();
	ms_rep_loop();
	return (0);
}
