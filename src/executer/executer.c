/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/08 17:45:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, execve
#include <sys/fcntl.h> // open
#include <stdlib.h> // malloc, free, exit
#include <stdio.h> // printf
#include <limits.h> // ARG_MAX
#include <sys/errno.h> // errno macros

#define ERR_CMD "command not found"

extern char	**environ;

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

// @todo free_cmd_table function

t_cmd_table	*create_cmd_table(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	t_ast		*temp;
	int			i;

	temp = ast;
	i = 0;
	while (temp && temp->token->desc == TOK_WORD)
	{
		temp = temp->left;
		i++;
	}
	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ast && ast->token->desc == TOK_WORD)
	{
		cmd_table->cmd[i] = ast->token->word;
		ast = ast->left;
		i++;
	}
	cmd_table->cmd[i] = NULL;
	cmd_table->fd_in = STDIN_FILENO;
	cmd_table->fd_out = STDOUT_FILENO;
	return (cmd_table);
}

int	get_heredoc(char *limiter)
{
	int		fd[2];
	int		limiter_len;
	char	*line;
	int		i;

	pipe(fd);
	limiter_len = ft_strlen(limiter);
	line = malloc(ARG_MAX * sizeof(char));
	i = 0;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		i = read(STDOUT_FILENO, line, ARG_MAX);
		line[i] = 0;
		if (line[limiter_len] == '\n'
			&& !ft_strncmp(line, limiter, limiter_len))
			break ;
		write(fd[1], line, i);
	}
	close(fd[1]);
	free(line);
	return (fd[0]);
}

pid_t	exec_cmd(t_cmd_table *cmd_table)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	path = get_cmd_path(environ, cmd_table->cmd[0]);
	if (!path)
	{
		exit_status_set(127);
		return (-1);
	}
	pid = fork();
	if (pid != 0)
		return (pid);
	dup2(cmd_table->fd_in, STDIN_FILENO);
	dup2(cmd_table->fd_out, STDOUT_FILENO);
	status = execve(path, cmd_table->cmd, environ);
	close(cmd_table->fd_in);
	close(cmd_table->fd_out);
	exit(status);
}

t_cmd_table	*handle_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = create_cmd_table(ast);
	return (cmd_table);
}

t_cmd_table	*handle_redir_heredoc(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_in
		= get_heredoc(ast->right->token->word);
	return (cmd_table);
}

t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
		exit_status_set(1);
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

	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (cmd_table);
}

t_cmd_table	*handle_pipe(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	int			fd[2];
	pid_t		pid_l;

	if (!ast)
		return (NULL);
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

	if (!ast)
		return (NULL);
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

	if (!ast)
		return (NULL);
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

static char	*exit_status_init(void)
{
	static char	exit_status = 0;

	return (&exit_status);
}

void	exit_status_set(char exit_status)
{
	*exit_status_init() = exit_status;
}

char	exit_status_get(void)
{
	return (*exit_status_init());
}

static t_ast	**invalid_ast_init(void)
{
	static t_ast	*ast = NULL;

	return (&ast);
}

void	invalid_ast_set(t_ast *invalid_ast)
{
	*invalid_ast_init() = invalid_ast;
}

t_ast	*invalid_ast_get(void)
{
	return(*invalid_ast_init());
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
			return (exit_status_get());
		waitpid(pid, &status, 0);
	}
	exit_status_set(0);
	return (exit_status_get());
}

// error in cmd table
// print inside executer
// status pointer in exec funcs + return faulty ast node

// syntax error exit status: 258
// execve exit status
// open exit status
// path not found exit status: command not found: 127