/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 17:29:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // ERR_* defines
#include <sys/types.h> // pid_t
#include <sys/errno.h> // errno macros
#include <unistd.h> // close, pipe
#include <sys/wait.h> // waitpid, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG

// @todo free_cmd_table function and free everything
// @todo revise code and remove unnecessary if statements
// @todo check for leaks and unclosed fds
// @todo check ping and /dev/random cases
// @todo integrate expander
// @todo errors into stderr

t_status	executer_exec_ast(t_ast *ast, int fd_in, int fd_out)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;

	errno = 0;
	ms_exit_status_set(ERR_SUCCESS);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (ms_exit_status_get() != ERR_SUCCESS)
		return (ms_exit_status_get());
	cmd_table = g_func_handle_arr[ast->token->desc](ast);
	if (!cmd_table)
		return (ms_exit_status_get());
	pid = exec_cmd(cmd_table, -1);
	if (pid != -1)
		ms_wait_pid_and_set_exit(pid);
	if (ms_exit_status_get() != ERR_GENERAL)
		ms_print_error(ms_exit_status_get(), 0, cmd_table->cmd[0]);
	while (waitpid(-1, NULL, WUNTRACED) != -1)
		;
	return (ms_exit_status_get());
}
