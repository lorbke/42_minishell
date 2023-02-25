/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 00:25:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include "libft.h" // ft_strdup
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <sys/errno.h> // errno macros
#include <string.h> // strerror
#include <stdbool.h> // bool

t_cmd_table	*redir_get_cmd_table(int redir_fd, t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (redir_fd == RETURN_ERROR)
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
	return (cmd_table);
}

bool	is_quoted(char desc)
{
	if (desc == TOK_QUOTED
		|| desc == TOK_UNCLOSED_SQUOTE
		|| desc == TOK_UNCLOSED_DQUOTE)
		return (true);
	return (false);
}

bool	is_word(char desc)
{
	if (desc == TOK_WORD || desc == TOK_SUBSHELL
		|| is_quoted(desc))
		return (true);
	return (false);
}

static char	**create_cmd_arr(t_ast *ast)
{
	char	**cmd_arr;
	t_ast	*temp;
	int		i;

	temp = ast;
	i = 0;
	while (temp && is_word(temp->token->desc))
	{
		temp = temp->left;
		i++;
	}
	cmd_arr = ft_malloc_safe(sizeof(char *), i + 1);
	i = 0;
	while (ast && is_word(ast->token->desc))
	{
		cmd_arr[i] = ft_strdup(ast->token->word);
		if (!cmd_arr[i])
			ft_perror_and_exit("executer: ft_strdup: malloc: ");
		i++;
		ast = ast->left;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

t_cmd_table	*create_cmd_table(t_ast *ast)
{
	t_cmd_table	*cmd_table;

	cmd_table = ft_malloc_safe(sizeof(t_cmd_table), 1);
	cmd_table->cmd = create_cmd_arr(ast);
	cmd_table->fd_in[0] = STDIN_FILENO;
	cmd_table->fd_out[0] = STDOUT_FILENO;
	cmd_table->fd_in[1] = FDLVL_STD;
	cmd_table->fd_out[1] = FDLVL_STD;
	return (cmd_table);
}
