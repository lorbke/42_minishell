/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:52:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 22:43:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // t_stack, t_token
#include <stdlib.h> // free

static void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->word)
		free(token->word);
	free(token);
}

void	lexer_free_tokstack(void *tokstack_void)
{
	t_stack	*tokstack;
	t_stack	*temp;

	tokstack = (t_stack *)tokstack_void;
	while (tokstack)
	{
		temp = tokstack;
		tokstack = tokstack->next;
		free_token(temp->token);
		free(temp);
	}
}
