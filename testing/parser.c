/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/14 15:29:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// merge identification and insertion?
// more efficient way to tokenize + parse?
// syntax error implemetation!
// if statements early in the functions or at the end?


// 1. get next token
// 2. quote identifier
// 	- if token contains quote, get next token until quote is closed
// 	- lots of quote edge cases
// 3. check for other special characters
// 	- heredoc
// 	- redirection and append
// 	- pipe
// 	- operator
// 	- word
// 4. insert node into AST
// (5. check for syntax errors)
// 6. repeat until EOF

#include "parser.h"

// every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// due to easier usage and because the additional memory and run time are negligible, 
// the token stack will be represented by a token_list instead of just a string

// how to handle syntax errors?

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

	if (!*tokstack || (*tokstack)->token->desc != 1)
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
		|| ((*tokstack)->token->desc != 3 && (*tokstack)->token->desc != 4))
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
	t_ast	*redir_in;
	t_ast	*word;
	t_ast	*redir_out;

	head = NULL;
	redir_in = rule_redirect(tokstack);
	word = rule_word(tokstack);
	redir_out = rule_redirect(tokstack);
	if (word)
		head = word;
	if (redir_in)
	{
		redir_in->left = head;
		head = redir_in;
	}
	if (redir_out)
	{
		redir_out->left = head;
		head = redir_out;
	}
	return (head);
}

t_ast	*parse(t_stack	*tokstack)
{
	t_ast	*ast;

	ast = rule_simple_cmd(&tokstack);
	return (ast);
}
