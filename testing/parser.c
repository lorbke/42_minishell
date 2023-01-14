/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/14 19:42:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// due to easier usage and because the additional memory and run time are negligible, 
// the token stack will be represented by a token_list instead of just a string

// how to handle syntax errors?
// = anywhere, where the grammar was not matched, e.g. simple_cmd without word

// free the tokstack after parsing

static t_ast	*create_ast_node(t_token	*token)
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

static t_ast	*rule_word(t_stack **tokstack)
{
	t_ast	*head;

	if (!*tokstack || (*tokstack)->token->desc != TOKEN_WORD)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->left = rule_word(tokstack);
	return (head);
}

static t_ast	*rule_redirect(t_stack **tokstack)
{
	t_ast	*head;

	if (!*tokstack
		|| ((*tokstack)->token->desc != TOKEN_REDIR_IN
			&& (*tokstack)->token->desc != TOKEN_REDIR_OUT))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	return (head);
}

static t_ast	*rule_simple_cmd(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*redir_start;
	t_ast	*word;
	t_ast	*redir_end;

	head = NULL;
	redir_start = rule_redirect(tokstack);
	word = rule_word(tokstack);
	redir_end = rule_redirect(tokstack);
	if (word)
		head = word;
	if (redir_start)
	{
		redir_start->left = head;
		head = redir_start;
	}
	if (redir_end)
	{
		redir_end->left = head;
		head = redir_end;
	}
	return (head);
}

t_ast	*parse(t_stack	*tokstack)
{
	t_ast	*ast;

	ast = rule_simple_cmd(&tokstack);
	return (ast);
}
