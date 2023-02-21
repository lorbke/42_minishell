/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:39 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 17:17:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // get_doc
#include "lexer.h" // lexer_str_to_tokstack
#include "libft.h" // ft_strjoin
#include "../minishell.h" // CMD_SEPS, CMD_ESCS
#include <stdlib.h> // free

char	*doccer_interpret_docs(t_stack *tokstack, char *input);

static char	*handle_unclosed_quote(char quote, char *input, t_stack *tokstack)
{
	char	*temp;
	char	*doc;

	tokstack->token->desc = TOK_WORD;
	temp = tokstack->token->word;
	doc = get_doc(doc_quotedoc, &quote);
	if (ms_exit_status_get() != ERR_SUCCESS)
		return (input);
	tokstack->token->word
		= ft_strjoin(tokstack->token->word, doc);
	free(temp);
	temp = input;
	input = ft_strjoin(input, doc);
	free(doc);
	free(temp);
	return (input);
}

static char	*handle_incomplete_input(char *input, t_stack *tokstack)
{
	char	*temp_str;
	char	*doc;

	doc = get_doc(doc_completingdoc, NULL);
	if (ms_exit_status_get() != ERR_SUCCESS)
		return (input);
	tokstack->next = lexer_str_to_tokstack(doc, CMD_SEPS, CMD_ESCS);
	temp_str = input;
	input = ft_strjoin(input, doc);
	free(doc);
	free(temp_str);
	return (input);
}

static t_stack
	*iterate_to_end_and_interpret_heredocs(t_stack *tokstack, char *input)
{
	char	*doc;
	t_stack	*temp_stack;

	while (tokstack)
	{
		if (tokstack->token->desc == TOK_REDIR_HEREDOC && tokstack->next)
		{
			doc = get_doc(doc_heredoc, tokstack->next->token->word);
			if (ms_exit_status_get() != ERR_SUCCESS)
				return (NULL);
			free(tokstack->next->token->word);
			tokstack->next->token->word = doc;
			tokstack = tokstack->next;
		}
		temp_stack = tokstack;
		tokstack = tokstack->next;
	}
	return (temp_stack);
}

char	*doccer_interpret_docs(t_stack *tokstack, char *input)
{
	t_stack	*temp_stack;

	temp_stack = iterate_to_end_and_interpret_heredocs(tokstack, input);
	if (!temp_stack)
		return (input);
	if (temp_stack->token->desc == TOK_UNCLOSED_SQUOTE)
		input = handle_unclosed_quote('\'', input, temp_stack);
	else if (temp_stack->token->desc == TOK_UNCLOSED_DQUOTE)
		input = handle_unclosed_quote('\"', input, temp_stack);
	else if (temp_stack->token->desc == TOK_PIPE
		|| temp_stack->token->desc == TOK_AND
		|| temp_stack->token->desc == TOK_OR)
	{
		input = handle_incomplete_input(input, temp_stack);
		if (temp_stack->next)
			input = doccer_interpret_docs(temp_stack->next, input);
	}
	return (input);
}
