/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:53:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 02:26:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

static bool	is_word(t_stack *token)
{
	if (!token)
		return (false);
	if (token->token->desc == TOK_WORD
		|| token->token->desc == TOK_UNCLOSED_SQUOTE
		|| token->token->desc == TOK_UNCLOSED_DQUOTE
		|| token->token->desc == TOK_QUOTED)
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

	if (!*tokstack || !is_redirect(*tokstack) || !is_word((*tokstack)->next))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	if (!(*tokstack)->next)
		return (head);
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
		head = append_left_ast(redirs_in, head);
	if (redirs_out)
		head = append_left_ast(redirs_out, head);
	return (head);
}

t_ast	*rule_simple_cmd(t_stack **tokstack)
{
	t_ast	*redirs_in;
	t_ast	*words;
	t_ast	*redirs_out;

	words = handle_subshell(tokstack);
	redirs_in = NULL;
	redirs_out = NULL;
	while (*tokstack && (is_word(*tokstack)
			|| (is_redirect(*tokstack) && is_word((*tokstack)->next))))
	{
		if (*tokstack && ((*tokstack)->token->desc == TOK_REDIR_IN
				|| (*tokstack)->token->desc == TOK_REDIR_HEREDOC))
			redirs_in = append_left_ast(rule_redirect(tokstack), redirs_in);
		if (*tokstack && ((*tokstack)->token->desc == TOK_REDIR_OUT
				|| (*tokstack)->token->desc == TOK_REDIR_APPEND))
			redirs_out = append_left_ast(rule_redirect(tokstack), redirs_out);
		if (!words || words->token->desc != TOK_SUBSHELL)
			words = append_left_ast(words, rule_word(tokstack));
		if (is_word(*tokstack) && words->token->desc == TOK_SUBSHELL)
			break ;
	}
	return (connect_simple_cmd(redirs_in, words, redirs_out));
}
