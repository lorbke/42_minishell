/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_interpret.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:25:39 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/01 00:27:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // get_doc
#include "lexer.h" // lexer_str_to_tokstack
#include "libft.h" // ft_strjoin
#include "garbage_collector.h" // gc_add_garbage
#include <stdlib.h> // free

/**
 * It iterates through the
 * token stack, and if it finds a heredoc token, it gets the heredoc and replaces
 * the next token with it
 * 
 * @param tokstack a pointer to the first token in the stack
 * @param exit_status This is a pointer to a t_status variable. 
 * This is the variable that
 * 
 * @return The last element in the stack.
 */
static t_stack	*iterate_to_end_and_interpret_heredocs(
	t_stack *tokstack, t_status *exit_status)
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

/**
 * If the input is incomplete, then we get the rest of the 
 * input and add it to the token stack
 * 
 * @param tokstack the token stack that we're currently working on
 * @param exit_status This is a pointer to the exit status of the shell.
 * @param input the input string
 * @param doc the string that is being read from the file
 * 
 * @return A t_stack
 */
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

/**
 * It takes a string of input,
 * and returns a stack of tokens
 * 
 * @param input the input string
 * @param exit_status This is the exit status of the shell.
 * 
 * @return A t_stack of tokens.
 */
t_stack	*doccer_get_complete_tokstack(char **input, t_status *exit_status)
{
	t_stack	*tokstack;
	t_stack	*prev;
	char	*doc;

	tokstack = lexer_str_to_tokstack(*input);
	if (!tokstack || !tokstack->next)
		return (tokstack);
	prev = iterate_to_end_and_interpret_heredocs(tokstack, exit_status);
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
