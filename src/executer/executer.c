/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/11 12:17:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // t_cmd_table, t_func_handle
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

// @todo free_cmd_table function and free everything
// @todo fix heredoc and unclosed && and || and |
// @todo heredoc signals
// @todo revise code and remove unnecessary if statements
// @todo check for leaks and unclosed fds
// @todo check ping and /dev/random cases
// @todo subshell
// @todo integrate expander

// free unclosed ast
void	get_unclosed(t_ast *ast)
{
	char	*heredoc;
	t_stack	*heredoc_tokstack;
	t_ast	*heredoc_ast;

	if ((ast->token->desc == TOK_AND
			|| ast->token->desc == TOK_OR
			|| ast->token->desc == TOK_PIPE)
			&& ast->right->token->desc == TOK_UNCLOSED)
	{
		heredoc = malloc(sizeof(char) * ARG_MAX);
		read(get_heredoc(&heredoc_small, NULL), heredoc, ARG_MAX);
		heredoc_tokstack = lexer_str_to_tokstack(heredoc, CMD_SEPS, CMD_ESCS);
		heredoc_ast = parser_tokstack_to_ast(&heredoc_tokstack);
		ast->right = heredoc_ast;
	}
}

char	executer_exec_ast(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;
	int			status;

	if (!ast)
		return (EXEC_SUCCESS);
	exit_status_set(EXEC_SUCCESS);
	get_unclosed(ast);
	cmd_table = g_func_handle_arr[ast->token->desc](ast);
	if (!cmd_table)
		return (exit_status_get());
	pid = exec_cmd(cmd_table);
	if (pid == -1)
	{
		print_error(exit_status_get(), cmd_table->cmd[0]);
		return (exit_status_get());
	}
	waitpid(pid, &status, 0);
	exit_status_set(WEXITSTATUS(status));
	return (exit_status_get());
}
