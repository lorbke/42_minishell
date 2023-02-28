/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:50 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:36:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include "libft.h" // ft_strdup
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

/**
 * It duplicates a token
 * 
 * @param token the token to duplicate
 * 
 * @return A copy of the token.
 */
static t_token	*dup_token(t_token *token)
{
	t_token	*new;

	new = ft_malloc_safe(sizeof(t_token), 1);
	new->desc = token->desc;
	if (token->word)
	{
		new->word = ft_strdup(token->word);
		if (!new->word)
			ft_perror_and_exit("parser: ft_strdup: malloc: ");
	}
	else
		new->word = NULL;
	return (new);
}

/**
 * It creates a new ast node,
 * and sets the token to the token passed in, and sets the left and
 * right pointers.
 * to NULL
 * 
 * @param token The token to be added to the tree.
 * 
 * @return A pointer to a new t_ast node.
 */
t_ast	*create_ast_node(t_token	*token)
{
	t_ast	*new;

	if (!token)
		return (NULL);
	new = ft_malloc_safe(sizeof(t_ast), 1);
	if (token->word)
		new->token = dup_token(token);
	else
		new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

/**
 * It appends the right ast node to the main ast node.
 * 
 * @param main The main ast node that we're appending to.
 * @param append The node to be appended to the left of the main node.
 * 
 * @return The main ast node.
 */
t_ast	*append_left_ast(t_ast *main, t_ast *append)
{
	t_ast	*temp;

	if (!main)
		return (append);
	temp = main;
	while (temp->left)
		temp = temp->left;
	temp->left = append;
	return (main);
}

/**
 * It returns true if the token is a word or quoted token
 * 
 * @param token The token to check.
 * 
 * @return A boolean value.
 */
bool	is_word(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOK_WORD
		|| token->token->desc == TOK_QUOTED)
		return (true);
	return (false);
}

/**
 * It returns true if the token is a redirection token
 * 
 * @param token The token to check.
 * 
 * @return A boolean value.
 */
bool	is_redirect(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOK_REDIR_IN
		|| token->token->desc == TOK_REDIR_OUT
		|| token->token->desc == TOK_REDIR_APPEND
		|| token->token->desc == TOK_REDIR_HEREDOC)
		return (true);
	return (false);
}
