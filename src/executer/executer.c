/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 14:45:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // error_exec_print
#include <sys/types.h> // pid_t
#include <sys/fcntl.h> // open
#include <sys/errno.h> // errno macros
#include <sys/wait.h> // waitpid
#include <string.h> // NULL
#include <unistd.h> // close, pipe
#include <limits.h> // ARG_MAX
#include <stdlib.h> // malloc, free
#include <stdio.h> // printf

// @todo free_cmd_table function and free everything
// @todo revise code and remove unnecessary if statements
// @todo check for leaks and unclosed fds
// @todo check ping and /dev/random cases
// @todo subshell
// @todo integrate expander
// @todo fix cat | ls and cat /dev/random | head -10 cases
// @todo errors into stderr
// @todo multiple shell levels ctrl c new line printed multiple times

void	print_error(t_status exit_status, char *error_loc)
{
	if (exit_status == EXEC_CMDNOTFOUND)
		printf("%s: %s: command not found\n", SHELL_NAME, error_loc);
	else if (exit_status >= EXEC_SIGNAL && exit_status <= EXEC_SIGNAL + 9)
		return ;
	else if (exit_status != EXEC_SUCCESS
		&& exit_status != EXEC_SYNTAXERR)
		printf("%s: %s: %s\n", SHELL_NAME, error_loc, strerror(errno));
}

// @todo free unclosed ast
// @note unclosed handling still ot like bash, e.g. history
static void	close_unclosed_branches(t_ast *ast)
{
	char	*heredoc;
	t_ast	*heredoc_ast;

	if (ast && (ast->token->desc == TOK_AND
			|| ast->token->desc == TOK_OR
			|| ast->token->desc == TOK_PIPE)
		&& ast->right->token->desc == TOK_UNCLOSED)
	{
		heredoc = malloc(sizeof(char) * ARG_MAX);
		read(get_heredoc(&heredoc_small, NULL), heredoc, ARG_MAX);
		heredoc_ast = input_to_ast(heredoc);
		if (!heredoc_ast && exit_status_get() == EXEC_SUCCESS)
			exit_status_set(EXEC_SYNTAXERR);
		free(heredoc);
		close_unclosed_branches(heredoc_ast);
		ast->right = heredoc_ast;
	}
}

// @todo fix echo hello | << lim cat (heredoc fd is overwritten)
// @todo fix echo hello && << lim cat (heredoc is not interpreted first)
// @todo fix ech hi | > teste case (file is opened even though ech hi fails)
t_status	executer_exec_ast(t_ast *ast, int fd_in, int fd_out)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;

	errno = 0;
	exit_status_set(EXEC_SUCCESS);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_unclosed_branches(ast);
	if (exit_status_get() != EXEC_SUCCESS)
		return (exit_status_get());
	cmd_table = g_func_handle_arr[ast->token->desc](ast);
	if (!cmd_table)
		return (exit_status_get());
	pid = exec_cmd(cmd_table, -1);
	if (pid != -1)
		wait_pid_and_set_exit(pid);
	if (exit_status_get() != EXEC_GENERALERR)
		print_error(exit_status_get(), cmd_table->cmd[0]);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
	return (exit_status_get());
}
