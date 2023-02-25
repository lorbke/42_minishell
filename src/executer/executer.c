/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 00:11:02 by lorbke           ###   ########.fr       */
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
#include <stdio.h> // printf

t_status	executer_exec_ast(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;

	cmd_table = g_func_handle_arr[ast->token->desc](ast);
	if (!cmd_table)
		return (ms_exit_status_get());
	pid = exec_cmd(cmd_table, RETURN_ERROR);
	ms_wait_pid_and_set_exit(pid);
	if (ms_exit_status_get() == ERR_CMDNOTFOUND
		|| ms_exit_status_get() == ERR_NOPERM
		|| ms_exit_status_get() == ERR_DIRNOTFOUND)
		ms_print_error(ms_exit_status_get(), 0, cmd_table->cmd[0]);
	while (waitpid(RETURN_ERROR, NULL, WUNTRACED) != RETURN_ERROR)
		;
	return (ms_exit_status_get());
}
