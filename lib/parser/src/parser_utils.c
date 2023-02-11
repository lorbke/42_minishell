/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:30:50 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/22 21:24:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

t_token	*create_token_unclosed(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->desc = TOK_UNCLOSED;
	new->word = NULL;
	return (new);
}

t_ast	*create_ast_node(t_token	*token)
{
	t_ast	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_ast));
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
