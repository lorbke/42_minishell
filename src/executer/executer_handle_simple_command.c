/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_handle_simple_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:27:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 15:48:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table, t_func_handle
#include "parser.h" // t_ast
#include "lexer.h" // t_token
#include "libft.h" // ft_strlen
#include "../minishell.h" // ERR_* defines
#include "../debugger.h" // debug functions
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
	if (!is_quoted(ast->right->token->desc))
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

t_cmd_table	*handle_redir_append(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	int			fd;

	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd_table = redir_get_cmd_table(fd, ast);
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
	cmd_table = redir_get_cmd_table(fd, ast);
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
	cmd_table = redir_get_cmd_table(fd, ast);
	if (!cmd_table)
		return (NULL);
	cmd_table->fd_out[0] = fd;
	cmd_table->fd_out[1] = FDLVL_REDIR;
	return (cmd_table);
}
