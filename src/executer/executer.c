/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 17:59:42 by lorbke           ###   ########.fr       */
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

// @todo free_cmd_table function and free everything
// @todo print error messages in the executer, because of or operator errors
// @todo fix heredoc and unclosed && and || and |
// @todo heredoc signals
// @todo revise code and remove unnecessary if statements
// @todo check for leaks and unclosed fds
// @todo check ping and /dev/random cases

char	executer_exec_ast(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;
	int			status;

	if (ast)
	{
		exit_status_set(0);
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
		// WEXITSTATUS extracts the exit status from the status returned by waitpid
		// status contains more information than just the exit status
		exit_status_set(WEXITSTATUS(status));
	}
	return (exit_status_get());
}
