/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:53:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:17:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

/**
 * If the token stack is empty or the top token is not a word, return NULL, 
 * otherwise create an AST node from the top token and pop the token stack
 * 
 * @param tokstack a pointer to the token stack
 * 
 * @return A pointer to a t_ast node.
 */
static t_ast	*rule_word(t_stack **tokstack)
{
	t_ast	*head;

	if (!*tokstack || !is_word(*tokstack))
		return (NULL);
	head = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	return (head);
}

/**
 * If the token stack is not empty, and the top token is a redirect, 
 * and the next token is a word, then create an AST node for the redirect, 
 * and set its right child to the word
 * 
 * @param tokstack a pointer to a pointer to a token stack.
 * 
 * @return The head of the tree.
 */
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

/**
 * It takes three ASTs, and
 * returns a new AST that is the concatenation of the three
 * 
 * @param redirs_in a list of redirections that are to be applied to the 
 * command's stdin
 * @param words a list of words, separated by spaces, 
 * that are the command and its arguments
 * @param redirs_out a list of redirections that are to the right 
 * of the command
 * 
 * @return The head of the AST.
 */
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

/**
 * It takes a token stack,
 * and returns an AST node representing a simple command
 * 
 * @param tokstack a pointer to a pointer to a t_stack. This is the token stack.
 * 
 * @return A pointer to a t_ast node.
 */
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
