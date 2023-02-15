/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/15 09:05:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h"
#include "executer.h" // t_cmd_table
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "libft.h" // ft_strlen, ft_strncmp
#include "../../../src/expander.h"
#include "../../../src/builtins.h" // all builtins
#include <sys/types.h> // pid_t, fork, execve
#include <fcntl.h> // open
#include <stdlib.h> // malloc, free, exit
#include <stdio.h> // printf
#include <limits.h> // ARG_MAX

extern t_sym_tab **g_sym_table;

static const t_func_handle func_handle_arr[]
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

// func create_cmd_table
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
	char	**env;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	env = create_env_list(g_sym_table);
	path = get_cmd_path(env, cmd_table->cmd[0]);
	cmd_table->cmd = expander(cmd_table->cmd);
	if (is_builtin(cmd_table->cmd[0]))
	{
		status = exec_builtin(cmd_table);
		return (status);
	}
	pid = fork();
	if (pid != 0)
		return (pid);
	dup2(cmd_table->fd_in, STDIN_FILENO);
	dup2(cmd_table->fd_out, STDOUT_FILENO);
	status = execve(path, cmd_table->cmd, env);
	close(cmd_table->fd_in);
	close(cmd_table->fd_out);
	exit(status);
}

// func for every (almost) toktype
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

	if (!ast)
		return (NULL);
	cmd_table = handle_cmd(ast->left);
	cmd_table->fd_in
		= get_heredoc(ast->right->token->word);
	return (cmd_table);
}

t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = handle_cmd(ast->left);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (cmd_table);
}

t_cmd_table	*handle_redir_in(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = handle_cmd(ast->left);
	cmd_table->fd_in
		= open(ast->right->token->word, O_RDONLY);
	return (cmd_table);
}

t_cmd_table	*handle_redir_out(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = handle_cmd(ast->left);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (cmd_table);
}

t_cmd_table	*handle_pipe(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	int			fd[2];

	if (!ast)
		return (NULL);
	pipe(fd);
	cmd_table_l = func_handle_arr[ast->left->token->desc](ast->left);
	cmd_table_l->fd_out = fd[1];
	exec_cmd(cmd_table_l);
	close(fd[1]);
	cmd_table_r = func_handle_arr[ast->right->token->desc](ast->right);
	cmd_table_r->fd_in = fd[0];
	return (cmd_table_r);
}

t_cmd_table *handle_and(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	if (!ast)
		return (NULL);
	cmd_table_l = func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l);
	waitpid(pid_l, &status, 0);
	if (status != 0)
		return (NULL);
	else
	{
		cmd_table_r = func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
}

t_cmd_table *handle_or(t_ast *ast)
{
	t_cmd_table	*cmd_table_l;
	t_cmd_table	*cmd_table_r;
	pid_t		pid_l;
	int			status;

	if (!ast)
		return (NULL);
	cmd_table_l = func_handle_arr[ast->left->token->desc](ast->left);
	pid_l = exec_cmd(cmd_table_l);
	waitpid(pid_l, &status, 0);
	if (status == 0)
		return (NULL);
	else
	{
		cmd_table_r = func_handle_arr[ast->right->token->desc](ast->right);
		return (cmd_table_r);
	}
}

void	executer_exec_ast(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	if (ast && ast->token)
	{
		cmd_table = func_handle_arr[ast->token->desc](ast);
		if (!cmd_table)
			return ;
		exec_cmd(cmd_table);
		while (wait(NULL) > 0);
	}
}
