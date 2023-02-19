/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:39 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:55:23 by lorbke           ###   ########.fr       */
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
	char	*temp_str;

	free(tokstack->token->word);
	tokstack->token->word = get_doc(doc_quotedoc, &quote);
	temp_str = input;
	input = ft_strjoin(input, tokstack->token->word);
	free(temp_str);
	return (input);
}

static char	*handle_incomplete_input(char *input, t_stack *tokstack)
{
	char	*temp_str;
	char	*doc;

	doc = get_doc(doc_completingdoc, NULL);
	tokstack->next = lexer_str_to_tokstack(doc, CMD_SEPS, CMD_ESCS);
	temp_str = input;
	input = ft_strjoin(input, doc);
	free(doc);
	input = doccer_interpret_docs(tokstack->next, input);
	return (input);
}

// @todo exit status handling
char	*doccer_interpret_docs(t_stack *tokstack, char *input)
{
	t_stack	*temp_stack;
	char	*doc;

	while (tokstack)
	{
		if (tokstack->token->desc == TOK_REDIR_HEREDOC && tokstack->next)
		{
			free(tokstack->token->word);
			tokstack->token->word
				= get_doc(doc_heredoc, tokstack->next->token->word);
		}
		temp_stack = tokstack;
		tokstack = tokstack->next;
	}
	if (temp_stack->token->desc == TOK_UNCLOSED_SQUOTE)
		input = handle_unclosed_quote('\'', input, temp_stack);
	else if (temp_stack->token->desc == TOK_UNCLOSED_DQUOTE)
		input = handle_unclosed_quote('\"', input, temp_stack);
	else if (temp_stack->token->desc == TOK_PIPE
		|| temp_stack->token->desc == TOK_AND
		|| temp_stack->token->desc == TOK_OR)
		input = handle_incomplete_input(input, temp_stack);
	return (input);
}
