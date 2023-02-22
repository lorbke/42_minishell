/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_gc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:15:32 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 20:08:19 by lorbke           ###   ########.fr       */
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

int	main(void)
{
	t_garbage	*garbage;
	char		*test;
	t_stack		*tokstack;
	t_ast		*ast;
	char		*input = "echo | asdfadsf asdsfasdfa asdsfasddfasd adsfasdsfasd  asdfasdfa";
	char		**strarr;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	gc_add_garbage(tokstack, &lexer_free_tokstack);
	ast = parser_tokstack_to_ast(&tokstack);
	gc_add_garbage(ast, &parser_free_ast);
	strarr = ft_split(input, ' ');
	gc_add_garbage(strarr, &gc_free_str_arr);
	gc_free_all_garbage();
	return (0);
}
