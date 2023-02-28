/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:39 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 21:41:06 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // get_doc
#include "lexer.h" // lexer_str_to_tokstack
#include "libft.h" // ft_strjoin
#include "../minishell.h" // CMD_SEPS, CMD_ESCS
#include <stdlib.h> // free
#include <stdbool.h> // bool


static bool	is_incomplete_input(t_stack *tokstack)
{
	if ((tokstack->token->desc == TOK_PIPE
			|| tokstack->token->desc == TOK_AND
		 	|| tokstack->token->desc == TOK_OR)
		&& tokstack->next == NULL)
		return (true);
	if (tokstack->token->desc == TOK_UNCLOSED_DQUOTE
		|| tokstack->token->desc == TOK_UNCLOSED_SQUOTE)
		return (true);
	return (false);
}


static t_stack	*iterate_to_end_and_interpret_heredocs(
	t_stack *tokstack, char *input, t_status *exit_status)
{
	char	*doc;
	t_stack	*temp_stack;

	while (tokstack)
	{
		if (tokstack->token->desc == TOK_REDIR_HEREDOC && tokstack->next)
		{
			doc = get_doc(
					doc_heredoc, tokstack->next->token->word, exit_status);
			if (*exit_status != ERR_SUCCESS)
			{
				free(doc);
				return (NULL);
			}
			free(tokstack->next->token->word);
			tokstack->next->token->word = doc;
			tokstack = tokstack->next;
		}
		temp_stack = tokstack;
		tokstack = tokstack->next;
	}
	return (temp_stack);
}

t_stack	*doccer_get_complete_tokstack(char **input, t_status *exit_status)
{
	t_stack *tokstack;
	t_stack *temp_stack;
	char	*temp_str;
	char	*doc;

	tokstack = lexer_str_to_tokstack(*input);
	if (!tokstack)
		return (NULL);
	temp_stack = iterate_to_end_and_interpret_heredocs(tokstack, *input, exit_status);
	if (!temp_stack)
		return (NULL);
	if (!is_incomplete_input(temp_stack))
		return (tokstack);
	doc = get_doc(doc_completingdoc, NULL, exit_status);
	if (!doc)
		return (NULL);
	temp_str = *input;
	*input = ft_strjoin(*input, doc);
	free(temp_str);
	tokstack->next = doccer_get_complete_tokstack(input, exit_status);
	free(doc);
	return (tokstack);
}
