/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 00:21:27 by lorbke           ###   ########.fr       */
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

static void	append_ast(t_ast *main, t_ast *append)
{
	while (main->left)
		main = main->left;
	main->left = append;
}

static t_ast	*rule_word(t_stack **tokstack, bool multiple)
{
	t_ast	*head;

	if (!*tokstack || (*tokstack)->token->desc != TOKEN_WORD)
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	if (multiple)
		head->left = rule_word(tokstack, 1);
	return (head);
}

static t_ast	*rule_redirect(t_stack **tokstack, bool multiple)
{
	t_ast	*head;
	t_ast	*next;

	if (!*tokstack
		|| ((*tokstack)->token->desc != TOKEN_REDIR_IN
			&& (*tokstack)->token->desc != TOKEN_REDIR_OUT
			&& (*tokstack)->token->desc != TOKEN_REDIR_APPEND
			&& (*tokstack)->token->desc != TOKEN_REDIR_HEREDOC))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_word(tokstack, 0);
	if (multiple)
	{
		next = rule_redirect(tokstack, 1);
		if (next)
		{
			append_ast(next, head);
			head = next;
		}
	}
	return (head);
}

static t_ast	*rule_simple_cmd(t_stack **tokstack)
{
	t_ast	*head;
	t_ast	*redir_in;
	t_ast	*word;
	t_ast	*redir_out;

	head = NULL;
	redir_in = rule_redirect(tokstack, 1);
	word = rule_word(tokstack, 1);
	redir_out = rule_redirect(tokstack, 1);
	if (word)
		head = word;
	if (redir_in)
	{
		append_ast(redir_in, head);
		head = redir_in;
	}
	if (redir_out)
	{
		append_ast(redir_out, head);
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
