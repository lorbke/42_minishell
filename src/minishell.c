/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/12 00:32:28 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free this 
	line;
	rl_clear_history();
*/

// unclear if EXIT check is needed, or if this can be done with termios
/* Read-Eval-Print-Loop. */
void	ms_rep_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line) // print exit
			break ;
		if (ft_strncmp(line, EXIT, sizeof(EXIT)) == 0)
			break ;
		if (*line)
		{
			add_history(line);
			write(1, "Input: ", 7);
			write(1, line, ft_strlen(line));
			write(1, "\n", 1);
		}
	}
}

/* Debug function to print the terminal settings. */
void	print_termios(struct termios *termios)
{
	printf("termios:\n");
	printf("	input mode: %lx\n", termios->c_iflag);
	printf("	output mode: %lx\n", termios->c_oflag);
	printf("	control mode: %lx\n", termios->c_cflag);
	printf("	local mode: %lx\n", termios->c_lflag);
	printf("	control characters: %hhu\n", termios->c_cc[VQUIT]);
	printf("	input speed: %lu\n", termios->c_ispeed);
	printf("	output speed: %lu\n", termios->c_ospeed);
}

/* Initializes the terminal settings. */
int	init_termios(void)
{
	struct termios	term_set;

	if (tcgetattr(STDIN_FILENO, &term_set) == -1)
		return (ERROR);

	term_set.c_lflag &= ~ECHOCTL; // this will prevent ^C from being printed (bitwise NOT)

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_set) == -1) // TCSANOW: change attributes immediately
		return (ERROR);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{

	if ((init_termios() == ERROR))
		return (EXIT_FAILURE);

	ms_init_signals();
	// check if stdin is a terminal
	if (isatty(STDIN_FILENO))
		ms_rep_loop();
		// else put input directly from STDIN to parser, executer etc

	return (EXIT_SUCCESS);
}
