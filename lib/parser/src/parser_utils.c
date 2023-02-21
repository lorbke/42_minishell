/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:50 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 18:13:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include "libft.h" // ft_strdup
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

t_token	*create_token_empty(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->desc = TOK_WORD;
	new->word = NULL;
	return (new);
}

static t_token	*dup_token(t_token *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->desc = token->desc;
	if (token->word)
		new->word = ft_strdup(token->word);
	else
		new->word = NULL;
	return (new);
}

t_ast	*create_ast_node(t_token	*token)
{
	t_ast	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
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

t_ast	*handle_subshell(t_stack **tokstack)
{
	t_ast	*new;

	if (!tokstack || !*tokstack || (*tokstack)->token->desc != TOK_SUBSHELL)
		return (NULL);
	new = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	return (new);
}
