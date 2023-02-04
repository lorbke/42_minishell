/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/24 18:30:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h"
#include "executer.h" // t_cmd_table
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include <unistd.h> // execve, fork
#include <fcntl.h> // open
#include <stdlib.h> // malloc
#include <stdio.h> // printf

static const t_func_handle func_handle_arr[]
= {
	[TOK_WORD] = &handle_cmd,
	[TOK_PIPE] = &handle_pipe,
	[TOK_REDIR_IN] = &handle_redir_in,
	[TOK_REDIR_OUT] = &handle_redir_out,
	[TOK_REDIR_HEREDOC] = &handle_cmd,
	[TOK_REDIR_APPEND] = &handle_cmd,
	[TOK_SQUOTE] = &handle_cmd,
	[TOK_DQUOTE] = &handle_cmd,
	[TOK_SUBSHELL] = &handle_cmd,
	[TOK_AND] = &handle_cmd,
	[TOK_OR] = &handle_cmd,
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

// func execute cmd_table
void	exec_cmd(t_cmd_table *cmd_table)
{
	pid_t	pid;

	if (!cmd_table)
		return ;
	pid = fork();
	if (pid == 0)
	{
		dup2(cmd_table->fd_in, STDIN_FILENO);
		dup2(cmd_table->fd_out, STDOUT_FILENO);
		execve(cmd_table->cmd[0], cmd_table->cmd, NULL);
		close(cmd_table->fd_in);
		close(cmd_table->fd_out);
	}
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
	cmd_table_r = func_handle_arr[ast->right->token->desc](ast->right);
	cmd_table_r->fd_in = fd[0];
	exec_cmd(cmd_table_l);
	close(fd[1]);
	return (cmd_table_r);
}

void	executer_exec_ast(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	if (ast && ast->token)
	{
		cmd_table = func_handle_arr[ast->token->desc](ast);
		exec_cmd(cmd_table);
		// close(cmd_table->fd_in);
	}
}
