/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:39 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 16:52:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // get_doc
#include "lexer.h" // lexer_str_to_tokstack
#include "libft.h" // ft_strjoin
#include <stdlib.h> // free

static t_stack	*iterate_to_end_and_interpret_heredocs(
	t_stack *tokstack, char *input, t_status *exit_status)
{
	char	*doc;
	t_stack	*temp_stack;

	while (tokstack->next)
	{
		if (tokstack->token->desc == TOK_REDIR_HEREDOC && tokstack->next
			&& doccer_is_word(tokstack->next->token->desc))
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
		}
		temp_stack = tokstack;
		tokstack = tokstack->next;
	}
	return (temp_stack);
}

t_stack	*doccer_get_complete_tokstack(char **input, t_status *exit_status);

static void	get_tail_stack(
	t_stack *tokstack, t_status *exit_status, char **input, char *doc)
{
	char	*temp_str;
	char	*temp_str2;
	int		len;

	if (is_incomplete_input(tokstack) == 1)
	{
		temp_str = *input;
		*input = ft_strjoin(*input, doc);
		tokstack->next->next = doccer_get_complete_tokstack(&doc, exit_status);
		free(doc);
		return ;
	}
	temp_str2 = tokstack->next->token->word;
	len = ft_strlen(temp_str2);
	temp_str = ft_strjoin(tokstack->next->token->word, doc);
	lexer_free_token(tokstack->next->token);
	free(tokstack->next);
	tokstack->next = doccer_get_complete_tokstack(&temp_str, exit_status);
	temp_str += len;
	temp_str2 = *input;
	*input = ft_strjoin(*input, temp_str);
	free(doc);
}

t_stack	*doccer_get_complete_tokstack(char **input, t_status *exit_status)
{
	t_stack	*tokstack;
	t_stack	*prev;
	char	*doc;

	tokstack = lexer_str_to_tokstack(*input);
	if (!tokstack || !tokstack->next)
		return (tokstack);
	prev = iterate_to_end_and_interpret_heredocs(tokstack, *input, exit_status);
	if (!prev)
		return (tokstack);
	if (!is_incomplete_input(prev))
		return (tokstack);
	doc = get_doc(doc_completingdoc, NULL, exit_status);
	if (!doc)
		return (tokstack);
	get_tail_stack(prev, exit_status, input, doc);
	return (tokstack);
}
