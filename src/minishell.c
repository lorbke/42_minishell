/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/10 20:35:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free this 
	free(line);
	rl_clear_history();
*/

// unclear if EXIT check is needed, or if this can be done with termios
/* Read-Eval-Print-Loop */
void	ms_rep_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
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

int	main(void)
{
	// check if stdin is a terminal
	if (!isatty(STDIN_FILENO))
	{
		write(2, "Error: Not a terminal\n", 22);
		return (1);
	}

	// get env values
	printf("%s", getenv("TERM"));

	tgetent(NULL, getenv("TERM"));

	ms_init_signals();
	ms_rep_loop();

	
	return (0);
}
