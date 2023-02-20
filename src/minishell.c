/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:50:40 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 23:21:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // macros
#include "mssignal.h" // mssignal_change_mode
#include "lexer.h" // lexer_str_to_tokstack
#include "parser.h" // parser_tokstack_to_ast
#include "doccer.h" // doccer_interpret_heredocs
#include "executer.h" // executer_exec_ast
#include "debugger.h" // debug
#include "libft.h" // ft_strncmp
#include <unistd.h> // file descriptor macros
#include <stdio.h> // printf
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <fcntl.h>

// @todo free the ast and the tokstack
// @todo test if all fds are closed
// @todo exit behaviour: print exit when ctrl+d is pressed (is that handled in exit builtin?)
// @todo documentation with some kind of tool
// @todo improve the debugger
// @todo rethink function names in minishell.h
// @todo exit status handling
// @todo error protections (malloc, open, etc.)
// @todo fix bug: overwriting first input when term window is exceeded
// @todo is not a terminal case handling
// @todo turn on wall werror wextra in every makefile
// @todo leak cases: echo | -> incomplete echo | -> incomplete, <<lim cat segfaults


/* Read-Eval-Print-Loop. */
void	rep_loop(void)
{
	char	*line;

	mssignal_change_mode(MSSIG_INTER);
	while (1)
	{
		open(STDIN_FILENO, O_RDONLY);
		line = readline(PROMPT);
		if (!line || ft_strncmp(line, "exit", 5) == 0) // exit buildin will be added later
			break ;
		if (*line)
		{
			line = digest_input(line, STDIN_FILENO, STDOUT_FILENO);
			add_history(line);
		}
		free(line);
		printf("exit_status: %d\n", exit_status_get());
	}
	rl_clear_history();
}

int	main(void)
{
	if (isatty(STDIN_FILENO)) // check if stdin is a terminal
		rep_loop();
	// else put input directly from STDIN to parser, executer etc
	mssignal_change_mode(MSSIG_NINTER);
	return (EXIT_SUCCESS);
}
