/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_and_or.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:30:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:24:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // ERR_* defines
#include "../debugger.h" // debug functions
#include <sys/types.h> // pid_t
#include <sys/fcntl.h> // open
#include <sys/wait.h> // waitpid
#include <string.h> // NULL
#include <unistd.h> // close, pipe

/**
 * It executes the left side of the `&&` operation, and if it succeeds, 
 * it executes the right side
 * 
 * @param ast the AST node that is being handled
 * 
 * @return A command table.
 */
t_cmd_table	*handle_and(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;

	debug_message("handling and operation.....\n", 1);
	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l, RETURN_ERROR);
	if (pid_l == RETURN_ERROR && ms_exit_status_get() != ERR_SUCCESS)
		return (NULL);
	if (pid_l != RETURN_ERROR)
		ms_wait_pid_and_set_exit(pid_l);
	if (ms_exit_status_get() == ERR_SUCCESS)
	{
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
	return (NULL);
}

/**
 * It executes the left side of the AST, and if it returns an error, 
 * it executes the right side of the
 * AST
 * 
 * @param ast the ast node that is being handled
 * 
 * @return A command table.
 */
t_cmd_table	*handle_or(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;

	debug_message("handling or operation......\n", 1);
	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l, RETURN_ERROR);
	if (pid_l != RETURN_ERROR)
		ms_wait_pid_and_set_exit(pid_l);
	if (ms_exit_status_get() != ERR_SUCCESS)
	{
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
	return (NULL);
}
