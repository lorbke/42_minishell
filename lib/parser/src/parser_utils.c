/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:50 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 20:34:27 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include "libft.h" // ft_strdup
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

static t_token	*dup_token(t_token *token)
{
	t_token	*new;

	new = ft_malloc_safe(sizeof(t_token), 1);
	new->desc = token->desc;
	if (token->word)
	{
		new->word = ft_strdup(token->word);
		if (!new->word)
			utils_ft_perror_and_exit("parser: ft_strdup: malloc: ");
	}
	else
		new->word = NULL;
	return (new);
}

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

bool	is_word(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOK_WORD
		|| token->token->desc == TOK_QUOTED)
		return (true);
	return (false);
}

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
