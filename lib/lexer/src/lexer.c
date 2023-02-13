/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:04:01 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/13 14:26:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // TOK_* macros, t_token, t_stack
#include "lexer_private.h" // main header
#include <stdlib.h> // for NULL

// @note where to handle token specific errors like only one &, unnmatched quotes, etc.?
// @note quotes are not identified properly - do they have to be identified?
static unsigned char	desc_word(char *word)
{
	if (*word == '|' && *(word + 1) != '|')
		return (TOK_PIPE);
	else if (*word == '<' && *(word + 1) == '<')
		return (TOK_REDIR_HEREDOC);
	else if (*word == '>' && *(word + 1) == '>')
		return (TOK_REDIR_APPEND);
	else if (*word == '<')
		return (TOK_REDIR_IN);
	else if (*word == '>')
		return (TOK_REDIR_OUT);
	else if (*word == '\'')
		return (TOK_WORD);
	else if (*word == '"')
		return (TOK_WORD);
	else if (*word == '(')
		return (TOK_SUBSHELL);
	else if (*word == '&' && *(word + 1) == '&')
		return (TOK_AND);
	else if (*word == '|' && *(word + 1) == '|')
		return (TOK_OR);
	return (TOK_WORD);
}

static t_token	*create_token(char *word)
{
	t_token	*new;

	if (!word || !*word)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->word = word;
	new->desc = desc_word(word);
	return (new);
}

static t_stack	*create_stack_node(t_token *token)
{
	t_stack	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_stack));
	new->token = token;
	new->next = NULL;
	return (new);
}

// @note ugly code, fix?
t_stack	*lexer_str_to_tokstack(char *str, char *seps, char *esc)
{
	t_stack	*head;
	t_stack	*temp;

	str = insert_sep_around_special(str, seps);
	head = NULL;
	while (*str)
	{
		head
			= create_stack_node(create_token(lexer_ft_strsep(&str, seps, esc)));
		if (head)
			break ;
	}
	if (!head)
		return (NULL);
	temp = head;
	while (*str)
	{
		temp->next
			= create_stack_node(create_token(lexer_ft_strsep(&str, seps, esc)));
		if (temp->next)
			temp = temp->next;
	}
	temp->next = NULL;
	return (head);
}
