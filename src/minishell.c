/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/14 15:29:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Read-Eval-Print-Loop. */
void	ms_rep_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line) // exit buildin will be added later
			break ;
		if (ft_strncmp(line, "exit", 5) == 0) // exit buildin will be added later
			break ;
		add_history(line);
		free(line);
	}
	rl_clear_history();
}

/* Initializes the terminal settings according to mode. */
int	init_termios(bool mode)
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
	if (init_termios(true) == ERROR)
		return (EXIT_FAILURE);
	ms_init_signals();

	char *sep = "\\/:;=-";
	char *test = "test/test2/test3";
	ft_strsep(&test, sep);
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		ms_rep_loop();
	// else put input directly from STDIN to parser, executer etc
	return (EXIT_SUCCESS);
}
