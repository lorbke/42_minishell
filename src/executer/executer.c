/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 14:51:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // t_cmd_table, t_func_handle
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include <sys/types.h> // pid_t
#include <sys/fcntl.h> // open
#include <sys/errno.h> // errno macros
#include <sys/wait.h> // waitpid
#include <string.h> // NULL
#include <unistd.h> // close, pipe

static const t_func_handle	g_func_handle_arr[]
	= {
[TOK_WORD] = &handle_cmd,
[TOK_PIPE] = &handle_pipe,
[TOK_REDIR_IN] = &handle_redir_in,
[TOK_REDIR_OUT] = &handle_redir_out,
[TOK_REDIR_HEREDOC] = &handle_redir_heredoc,
[TOK_REDIR_APPEND] = &handle_redir_append,
[TOK_SQUOTE] = &handle_cmd,
[TOK_DQUOTE] = &handle_cmd,
[TOK_SUBSHELL] = &handle_cmd,
[TOK_AND] = &handle_and,
[TOK_OR] = &handle_or,
};

// @todo free_cmd_table function and free everything
// @todo fix case: echo 1 && ec 2 || echo 3 && echo 4
// @todo fix case: echo hi && ech || echo hey
// @todo fix heredoc and unclosed && and || and |
// @todo heredoc signals
// @todo revise code and remove unnecessary if statements
// @todo check for leaks and unclosed fds
// @todo check ping and /dev/random cases

t_cmd_table	*handle_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = create_cmd_table(ast);
	return (cmd_table);
}

t_cmd_table	*handle_redir_heredoc(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = get_heredoc(ast->right->token->word);
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_in = fd;
	return (cmd_table);
}

t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out = fd;
	return (cmd_table);
}

t_cmd_table	*handle_redir_in(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_RDONLY);
	if (fd == -1)
	{
		invalid_ast_set(ast->right);
		exit_status_set(EXEC_GENERALERR);
		return (NULL);
	}
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_in = fd;
	return (cmd_table);
}

t_cmd_table	*handle_redir_out(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out = fd;
	return (cmd_table);
}

t_cmd_table	*handle_pipe(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	int			fd[2];
	pid_t		pid_l;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table_l)
		return (NULL);
	pipe(fd);
	cmd_table_l->fd_out = fd[1];
	pid_l = exec_cmd(cmd_table_l);
	close(fd[1]);
	if (pid_l == -1)
	{
		invalid_ast_set(ast->left);
		return (NULL);
	}
	cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
	if (!cmd_table_r)
		return (NULL);
	cmd_table_r->fd_in = fd[0];
	return (cmd_table_r);
}

t_cmd_table	*handle_and(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table_l)
		return (NULL);
	pid_l = exec_cmd(cmd_table_l);
	waitpid(pid_l, &status, 0);
	if (pid_l == -1)
	{
		invalid_ast_set(ast->left);
		return (NULL);
	}
	if (status != 0)
		return (NULL);
	else
	{
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
}

t_cmd_table	*handle_or(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	cmd_table_l = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table_l)
		return (NULL);
	pid_l = exec_cmd(cmd_table_l);
	waitpid(pid_l, &status, 0);
	if (pid_l == -1)
	{
		invalid_ast_set(ast->left);
		return (NULL);
	}
	if (status == 0)
		return (NULL);
	else
	{
		cmd_table_r = g_func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
}

char	executer_exec_ast(t_ast **ast)
{
	t_cmd_table	*cmd_table;
	pid_t		pid;
	int			status;

	cmd_table = NULL;
	if (ast && *ast && (*ast)->token)
	{
		cmd_table = g_func_handle_arr[(*ast)->token->desc](*ast);
		if (!cmd_table)
		{
			*ast = invalid_ast_get();
			return (exit_status_get());
		}
		pid = exec_cmd(cmd_table);
		if (pid == -1)
		{
			exit_status_set(EXEC_CMDNOTFOUND);
			// @note mistakes are hidden here
			if ((*ast)->right)
				*ast = (*ast)->right;
			return (exit_status_get());
		}
		waitpid(pid, &status, 0);
	}
	exit_status_set(0);
	return (exit_status_get());
}
