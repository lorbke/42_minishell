/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:29:17 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/25 23:35:29 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // ERR_* defines
#include <sys/types.h> // pid_t
#include <string.h> // NULL
#include <unistd.h> // close, pipe

static void	set_fd(int fd[][2], int fd_new)
{
	if (fd[0][1] < FDLVL_PIPE)
	{
		fd[0][0] = fd_new;
		fd[0][1] = FDLVL_PIPE;
	}
	else
		close(fd_new);
}

t_cmd_table	*handle_pipe(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	int			fd_pipe[2];
	pid_t		pid_l;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (pipe(fd_pipe) == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		return (NULL);
	}
	if (cmd_table_l)
	{
		set_fd(&cmd_table_l->fd_out, fd_pipe[1]);
		pid_l = exec_cmd(cmd_table_l, fd_pipe[0]);
		if (pid_l == RETURN_ERROR)
			ms_print_error(ms_exit_status_get(), 0, cmd_table_l->cmd[0]);
	}
	else
		close(fd_pipe[1]);
	cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
	if (!cmd_table_r)
		return (NULL);
	set_fd(&cmd_table_r->fd_in, fd_pipe[0]);
	return (cmd_table_r);
}
