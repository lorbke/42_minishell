/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_simple_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:27:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 15:26:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // error_exec_print
#include <sys/fcntl.h> // open
#include <string.h> // NULL

t_cmd_table	*handle_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = create_cmd_table(ast);
	return (cmd_table);
}

// @todo heredocs are expanded, therefore this function must exist
// t_cmd_table	*handle_redir_heredoc(t_ast *ast)
// {
// 	t_cmd_table	*cmd_table;
// 	int			fd;

// 	fd = get_heredoc(&heredoc_big, ast->right->token->word);
// 	if (!ast->left)
// 		return (NULL);
// 	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
// 	if (!cmd_table)
// 		return (NULL);
// 	cmd_table->fd_in[0] = fd;
// 	cmd_table->fd_in[1] = FDLVL_REDIR;
// 	return (cmd_table);
// }

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
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}

t_cmd_table	*handle_redir_in(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_RDONLY);
	if (fd == -1)
	{
		exit_status_set(EXEC_GENERALERR);
		print_error(EXEC_GENERALERR, ast->right->token->word);
		return (NULL);
	}
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_in[0] = fd;
	cmd_table->fd_in[1] = FDLVL_REDIR;
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
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}
