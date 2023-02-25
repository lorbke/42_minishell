/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_simple_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:27:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/25 14:24:58 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "../minishell.h" // ERR_* defines
#include "../expander.h" // expander
#include "garbage_collector.h" // gc_add_garbage
#include <sys/fcntl.h> // open
#include <string.h> // NULL
#include <unistd.h> // pipe, write
#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

t_cmd_table	*handle_cmd(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = create_cmd_table(ast);
	if (!cmd_table)
		return (NULL);
	gc_add_garbage(cmd_table, &executer_free_cmd_table);
	return (cmd_table);
}

// @todo heredocs expansion
t_cmd_table	*handle_redir_heredoc(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	char		*temp;
	char		*expand;
	int			fd[2];

	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	pipe(fd);
	temp = ast->right->token->word;
	if (ast->right->token->desc != TOK_QUOTED
		&& ast->right->token->desc != TOK_UNCLOSED_DQUOTE
		&& ast->right->token->desc != TOK_UNCLOSED_SQUOTE)
		temp = expand_str(ast->right->token->word);
	expand = temp;
	while (temp && *temp)
	{
		write(fd[1], temp, 1);
		temp++;
	}
	close(fd[1]);
	if (expand != ast->right->token->word)
		free(expand);
	cmd_table->fd_in[0] = fd[0];
	cmd_table->fd_in[1] = FDLVL_REDIR;
	return (cmd_table);
}

t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		ms_print_error(ms_exit_status_get(), 0, ast->right->token->word);
		return (NULL);
	}
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
	if (fd == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		ms_print_error(ms_exit_status_get(), 0, ast->right->token->word);
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
	if (fd == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		ms_print_error(ms_exit_status_get(), 0, ast->right->token->word);
		return (NULL);
	}
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}
