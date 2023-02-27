/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:15:32 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 16:57:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"
#include "garbage_collector.h"
#include "executer.h"
#include "src/executer/private_executer.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "src/minishell.h"
#include "src/mssignal.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h>
#include <stdbool.h>

static bool	is_subshell_closed(char *str)
{
	int		depth;

	depth = 0;
	while (*str)
	{
		if (*str == '(')
			depth++;
		else if (*str == ')')
			depth--;
		str++;
	}
	if (!depth)
		return (true);
	return (false);
}

int	main(void)
{
	char		*input1 = ""; // 0
	char		*input2 = "echo"; // 0
	char		*input3 = "("; // 1
	char		*input4 = "()"; // 0
	char		*input5 = "()("; // 1
	char		*input6 = " ()( "; // 1
	char		*input7 = "(ech)o"; // 0
	char		*input8 = "(/bin/echo 1 | /bin/echo 2 && ((/bin/echo 3 | /bin/echo 3) | (/bin/echo 4 | /bin/echo 4)))"; // 1
	char		*input9 = "((echo)"; // 1
	char		*input10 = "((echo 1) | (echo 2) | (echo 3 | (echo 4)))"; // 0

	printf("input1: %d\n", is_subshell_closed(input1));
	printf("input2: %d\n", is_subshell_closed(input2));
	printf("input3: %d\n", is_subshell_closed(input3));
	printf("input4: %d\n", is_subshell_closed(input4));
	printf("input5: %d\n", is_subshell_closed(input5));
	printf("input6: %d\n", is_subshell_closed(input6));
	printf("input7: %d\n", is_subshell_closed(input7));
	printf("input8: %d\n", is_subshell_closed(input8));
	printf("input9: %d\n", is_subshell_closed(input9));
	printf("input10: %d\n", is_subshell_closed(input10));
	return (0);
}
