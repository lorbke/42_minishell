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

static const t_func_exec func_exec_arr[]
= {
	[TOK_WORD] = &exec_cmd,
	[TOK_PIPE] = &exec_cmd,
	[TOK_REDIR_IN] = &exec_cmd,
	[TOK_REDIR_OUT] = &exec_redir_out,
	[TOK_REDIR_APPEND] = &exec_cmd,
	[TOK_REDIR_HEREDOC] = &exec_cmd,
	[TOK_SQUOTE] = &exec_cmd,
	[TOK_DQUOTE] = &exec_cmd,
	[TOK_SUBSHELL] = &exec_cmd,
	[TOK_AND] = &exec_cmd,
	[TOK_OR] = &exec_cmd,
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
void	execute_cmd(t_cmd_table *cmd_table)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(cmd_table->fd_in, STDIN_FILENO);
		dup2(cmd_table->fd_out, STDOUT_FILENO);
		execve(cmd_table->cmd[0], cmd_table->cmd, NULL);
	}
	else
		waitpid(pid, NULL, 0);
}

// func for every (almost) toktype
t_cmd_table	*exec_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = create_cmd_table(ast);
	return (cmd_table);
}

t_cmd_table	*exec_redir_out(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (!ast)
		return (NULL);
	cmd_table = exec_cmd(ast->left);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (cmd_table);
}

void	executer(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	if (ast && ast->token)
	{
		cmd_table = func_exec_arr[ast->token->desc](ast);
		execute_cmd(cmd_table);
	}
}
