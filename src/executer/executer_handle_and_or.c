/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_and_or.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:30:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/13 15:12:29 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // t_cmd_table, t_func_handle
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // error_exec_print
#include <sys/types.h> // pid_t
#include <sys/fcntl.h> // open
#include <sys/wait.h> // waitpid
#include <string.h> // NULL
#include <unistd.h> // close, pipe

t_cmd_table	*handle_and(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l);
	if (pid_l == -1 && exit_status_get() != EXEC_SUCCESS)
	{
		print_error(exit_status_get(), cmd_table_l->cmd[0]);
		return (NULL);
	}
	if (pid_l != -1)
	{
		waitpid(pid_l, &status, 0);
		exit_status_set(WEXITSTATUS(status));
	}
	if (exit_status_get() == EXEC_SUCCESS)
	{
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
	return (NULL);
}

t_cmd_table	*handle_or(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l);
	if (pid_l != -1)
	{
		waitpid(pid_l, &status, 0);
		exit_status_set(WEXITSTATUS(status));
	}
	if (exit_status_get() != EXEC_SUCCESS)
	{
		print_error(exit_status_get(), cmd_table_l->cmd[0]);
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
	return (NULL);
}
