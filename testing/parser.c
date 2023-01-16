/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 01:08:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// due to easier usage and because the additional memory and run time are negligible, 
// the token stack will be represented by a token_list instead of just a string

// how to handle syntax errors?
// = anywhere, where the grammar was not matched, e.g. simple_cmd without word or redirect no word found

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

static t_ast	*append_ast(t_ast *main, t_ast *append)
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

static bool	is_word(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOKEN_WORD
		|| token->token->desc == TOKEN_SQUOTE
		|| token->token->desc == TOKEN_DQUOTE)
		return (true);
	return (false);
}

static bool	is_redirect(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOKEN_REDIR_IN
		|| token->token->desc == TOKEN_REDIR_OUT
		|| token->token->desc == TOKEN_REDIR_APPEND
		|| token->token->desc == TOKEN_REDIR_HEREDOC)
		return (true);
	return (false);
}

static t_ast	*rule_word(t_stack **tokstack)
{
	t_ast	*head;

	if (!*tokstack || !is_word(*tokstack))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	return (head);
}

static t_ast	*rule_redirect(t_stack **tokstack)
{
	t_ast	*head;

	if (!*tokstack || !is_redirect(*tokstack))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	head->right = rule_word(tokstack);
	return (head);
}

static t_ast	*rule_simple_cmd_connect(t_ast *redirs_in, t_ast *words, t_ast *redirs_out)
{
	t_ast	*head;

	head = NULL;
	if (words)
		head = words;
	if (redirs_in)
		head = append_ast(redirs_in, head);
	if (redirs_out)
		head = append_ast(redirs_out, head);
	return (head);
}

static t_ast	*rule_simple_cmd(t_stack **tokstack)
{
	t_ast	*redirs_in;
	t_ast	*words;
	t_ast	*redirs_out;

	redirs_in = NULL;
	words = NULL;
	redirs_out = NULL;
	while (*tokstack && (is_word(*tokstack) || is_redirect(*tokstack)))
	{
		if (*tokstack && ((*tokstack)->token->desc == TOKEN_REDIR_IN
				|| (*tokstack)->token->desc == TOKEN_REDIR_HEREDOC))
			redirs_in = append_ast(rule_redirect(tokstack), redirs_in);
		words = append_ast(words, rule_word(tokstack));
		if (*tokstack && ((*tokstack)->token->desc == TOKEN_REDIR_OUT
				|| (*tokstack)->token->desc == TOKEN_REDIR_APPEND))
			redirs_out = append_ast(rule_redirect(tokstack), redirs_out);
	}
	return (rule_simple_cmd_connect(redirs_in, words, redirs_out));
}

// you did well here copilot!!
// static t_ast	*rule_pipe(t_stack **tokstack)
// {
// 	t_ast	*head;
// 	t_ast	*left;
// 	t_ast	*right;

// 	if (!*tokstack || (*tokstack)->token->desc != TOKEN_PIPE)
// 		return (NULL);
// 	head = create_ast_node((*tokstack)->token);
// 	*tokstack = (*tokstack)->next;
// 	left = rule_simple_cmd(tokstack);
// 	right = rule_simple_cmd(tokstack);
// 	head->left = left;
// 	head->right = right;
// 	return (head);
// }

t_ast	*parse(t_stack	*tokstack)
{
	t_ast	*ast;

	ast = rule_simple_cmd(&tokstack);
	return (ast);
}
