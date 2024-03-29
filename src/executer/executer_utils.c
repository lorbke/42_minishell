/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/04 20:38:42 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include "libft.h" // ft_strdup
#include "../minishell.h" // print_error
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <sys/errno.h> // errno macros
#include <string.h> // strerror
#include <stdbool.h> // bool

/**
 * It gets the command table
 * for the left side of the redirection
 * 
 * @param redir_fd The file descriptor that the redirection will 
 * be performed on.
 * @param ast The AST node that represents the redirection.
 * 
 * @return A pointer to a t_cmd_table struct.
 */
t_cmd_table	*redir_get_cmd_table(int redir_fd, t_ast *ast)
{
	t_cmd_table	*cmd_table;

	if (redir_fd == RETURN_ERROR)
	{
		ms_exit_status_set(ERR_GENERAL);
		ms_print_errno(ast->right->token->word);
		return (NULL);
	}
	if (!ast->left)
		return (NULL);
	cmd_table = g_func_handle_arr[ast->left->token->desc](ast->left);
	if (!cmd_table)
		return (NULL);
	return (cmd_table);
}

/**
 * It returns true if the token is a word, a subshell, or a quoted string.
 * 
 * @param desc The token description.
 * 
 * @return A boolean value.
 */
bool	executer_is_quoted(char desc)
{
	if (desc == TOK_QUOTED
		|| desc == TOK_UNCLOSED_SQUOTE
		|| desc == TOK_UNCLOSED_DQUOTE)
		return (true);
	return (false);
}

/**
 * It returns true if the
 * token is a word, a subshell, or a quoted string
 * 
 * @param desc The token description.
 * 
 * @return A boolean value.
 */
bool	executer_is_word(char desc)
{
	if (desc == TOK_WORD || desc == TOK_SUBSHELL
		|| executer_is_quoted(desc))
		return (true);
	return (false);
}

/**
 * It creates an array of strings from the command name and arguments.
 * 
 * @param ast the ast node that represents the command
 * 
 * @return A char **
 */
static char	**create_cmd_arr(t_ast *ast)
{
	char	**cmd_arr;
	t_ast	*temp;
	int		i;

	temp = ast;
	i = 0;
	while (temp && executer_is_word(temp->token->desc))
	{
		temp = temp->left;
		i++;
	}
	cmd_arr = ft_malloc_safe(sizeof(char *), i + 1);
	i = 0;
	while (ast && executer_is_word(ast->token->desc))
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

/**
 * It creates a command table
 * from an AST
 * 
 * @param ast The AST node that represents the command.
 * 
 * @return A pointer to a t_cmd_table struct.
 */
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
