/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:52:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/01 00:26:08 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // t_stack, t_token
#include <stdlib.h> // free

/**
 * It frees a token
 * 
 * @param token The token to free.
 * 
 * @return A pointer to a t_token struct.
 */
void	lexer_free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->word)
		free(token->word);
	free(token);
}

/**
 * It frees the memory allocated for the token stack
 * 
 * @param tokstack_void This is the pointer to the stack of tokens.
 */
void	lexer_free_tokstack(void *tokstack_void)
{
	t_stack	*tokstack;
	t_stack	*temp;

	tokstack = (t_stack *)tokstack_void;
	while (tokstack)
	{
		temp = tokstack;
		tokstack = tokstack->next;
		lexer_free_token(temp->token);
		free(temp);
	}
}
