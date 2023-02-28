/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_simple_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:27:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:24:47 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "libft.h" // ft_strlen
#include "../minishell.h" // ERR_* defines
#include "../debugger.h" // debug functions
#include "../expander.h" // expander
#include "../globber.h" // globber
#include "garbage_collector.h" // gc_add_garbage
#include <sys/fcntl.h> // open
#include <string.h> // NULL
#include <unistd.h> // pipe, write
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

/**
 * It creates a command table
 * from the abstract syntax tree
 * 
 * @param ast The abstract syntax tree.
 * 
 * @return A pointer to a command table.
 */
t_cmd_table	*handle_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	debug_message("creating command table.....\n", 1);
	cmd_table = create_cmd_table(ast);
	if (!cmd_table)
		return (NULL);
	gc_add_garbage(cmd_table, &executer_free_cmd_table);
	return (cmd_table);
}

/**
 * It creates a pipe, writes the heredoc to the pipe, and then sets the 
 * input file descriptor of the
 * command table to the read end of the pipe
 * 
 * @param ast the AST node that represents the redirection
 * 
 * @return A pointer to a t_cmd_table struct.
 */
t_cmd_table	*handle_redir_heredoc(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd[2];

	debug_message("handling heredoc...........\n", 1);
	cmd_table = redir_get_cmd_table(0, ast);
	if (!cmd_table)
		return (NULL);
	if (pipe(fd) == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		return (NULL);
	}
	if (!executer_is_quoted(ast->right->token->desc))
	{
		gc_add_garbage(ast->right->token->word, NULL);
		ast->right->token->word = expand_str(ast->right->token->word);
	}
	if (ast->right->token->word)
		write(fd[1], ast->right->token->word,
			ft_strlen(ast->right->token->word));
	close(fd[1]);
	cmd_table->fd_in[0] = fd[0];
	cmd_table->fd_in[1] = FDLVL_REDIR;
	return (cmd_table);
}

/**
 * It opens a file in append mode, and then calls `redir_get_cmd_table` 
 * to get the command table
 * 
 * @param ast the AST node that represents the redirection
 * 
 * @return A pointer to a t_cmd_table struct.
 */
t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	debug_message("handling redirection append\n", 1);
	ast->right->token->word = globber_redirection(ast->right->token->word);
	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd_table = redir_get_cmd_table(fd, ast);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}

/**
 * It opens the file, creates a command table, and sets the file descriptor 
 * to the command table
 * 
 * @param ast the ast node that contains the redirection
 * 
 * @return A pointer to a t_cmd_table struct.
 */
t_cmd_table	*handle_redir_in(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	debug_message("handling redirection in....\n", 1);
	ast->right->token->word = globber_redirection(ast->right->token->word);
	fd = open(ast->right->token->word, O_RDONLY);
	cmd_table = redir_get_cmd_table(fd, ast);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_in[0] = fd;
	cmd_table->fd_in[1] = FDLVL_REDIR;
	return (cmd_table);
}

/**
 * It opens a file, creates a command table, and sets the file descriptor 
 * to the command table
 * 
 * @param ast the AST node that represents the redirection
 * 
 * @return A pointer to a t_cmd_table struct.
 */
t_cmd_table	*handle_redir_out(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	debug_message("handling redirection out...\n", 1);
	ast->right->token->word = globber_redirection(ast->right->token->word);
	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	cmd_table = redir_get_cmd_table(fd, ast);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}
