/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:53:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 14:47:46 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_word(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOK_WORD
		|| token->token->desc == TOK_SQUOTE
		|| token->token->desc == TOK_DQUOTE
		|| token->token->desc == TOK_SUBSHELL)
		return (true);
	return (false);
}

static bool	is_redirect(t_stack *token)
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

static t_ast	*connect_simple_cmd(
	t_ast *redirs_in, t_ast *words, t_ast *redirs_out)
{
	t_ast	*head;

	head = NULL;
	if (words)
		head = words;
	if (redirs_in)
		head = left_append_ast(redirs_in, head);
	if (redirs_out)
		head = left_append_ast(redirs_out, head);
	return (head);
}

t_ast	*rule_simple_cmd(t_stack **tokstack)
{
	t_ast	*redirs_in;
	t_ast	*words;
	t_ast	*redirs_out;

	if (!*tokstack)
		return (NULL);
	redirs_in = NULL;
	words = NULL;
	redirs_out = NULL;
	while (*tokstack && (is_word(*tokstack) || is_redirect(*tokstack)))
	{
		if (*tokstack && ((*tokstack)->token->desc == TOK_REDIR_IN
				|| (*tokstack)->token->desc == TOK_REDIR_HEREDOC))
			redirs_in = left_append_ast(rule_redirect(tokstack), redirs_in);
		words = left_append_ast(words, rule_word(tokstack));
		if (*tokstack && ((*tokstack)->token->desc == TOK_REDIR_OUT
				|| (*tokstack)->token->desc == TOK_REDIR_APPEND))
			redirs_out = left_append_ast(rule_redirect(tokstack), redirs_out);
	}
	return (connect_simple_cmd(redirs_in, words, redirs_out));
}
