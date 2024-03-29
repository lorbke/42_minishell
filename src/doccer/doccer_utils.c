/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:30:33 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:04:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strrchr
#include "lexer.h" // lexer_str_to_tokstack

/**
 * It returns true if the
 * token is quoted, false otherwise
 * 
 * @param desc The token description.
 */
static bool	executer_is_quoted(char desc)
{
	if (desc == TOK_QUOTED
		|| desc == TOK_UNCLOSED_SQUOTE
		|| desc == TOK_UNCLOSED_DQUOTE)
		return (true);
	return (false);
}

/**
 * It returns true if the
 * character is a word, a subshell, or a quoted character
 * 
 * @param desc The token description.
 */
bool	doccer_is_word(char desc)
{
	if (desc == TOK_WORD || desc == TOK_SUBSHELL
		|| executer_is_quoted(desc))
		return (true);
	return (false);
}

/**
 * It checks if the token stack is incomplete
 * 
 * @param tokstack the stack of tokens
 * 
 * @return The return value is an integer.
 */
int	is_incomplete_input(t_stack *tokstack)
{
	t_stack	*next;

	next = tokstack->next;
	if (doccer_is_word(tokstack->token->desc)
		&& (next->token->desc == TOK_PIPE
			|| next->token->desc == TOK_AND
			|| next->token->desc == TOK_OR)
		&& next->next == NULL)
		return (1);
	if (next->token->desc == TOK_UNCLOSED_DQUOTE
		|| next->token->desc == TOK_UNCLOSED_SQUOTE)
		return (2);
	return (0);
}
