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
t_cmd_table	*exec_cmd(t_ast *ast, void *func_exec)
{
	t_cmd_table	*cmd_table;
	t_func_exec	*func_exec_arr;

	if (!ast)
		return (NULL);
	func_exec_arr = (t_func_exec *)func_exec;
	cmd_table = create_cmd_table(ast);
	return (cmd_table);
}

t_cmd_table	*exec_redir_out(t_ast *ast, void *func_exec)
{
	t_cmd_table	*cmd_table;
	t_func_exec	*func_exec_arr;

	if (!ast)
		return (NULL);
	func_exec_arr = (t_func_exec *)func_exec;
	cmd_table = exec_cmd(ast->left, func_exec);
	cmd_table->fd_out
		= open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (cmd_table);
}

// func func_pointer_init
t_func_exec	*init_func_exec_arr(void)
{
	t_func_exec	*func_exec;

	func_exec = malloc(sizeof(t_func_exec) * 11);
	func_exec[0] = exec_cmd;
	func_exec[1] = exec_cmd;
	func_exec[2] = exec_cmd;
	func_exec[3] = exec_redir_out;
	func_exec[4] = exec_cmd;
	func_exec[5] = exec_cmd;
	func_exec[6] = exec_cmd;
	func_exec[7] = exec_cmd;
	func_exec[8] = exec_cmd;
	func_exec[9] = exec_cmd;
	func_exec[10] = exec_cmd;
	return (func_exec);
}

void	executer(t_ast *ast)
{
	t_func_exec	*func_exec;
	t_cmd_table	*cmd_table;

	cmd_table = NULL;
	func_exec = init_func_exec_arr();
	if (ast && ast->token)
	{
		cmd_table = func_exec[ast->token->desc](ast, (void *)func_exec);
		execute_cmd(cmd_table);
	}
}
