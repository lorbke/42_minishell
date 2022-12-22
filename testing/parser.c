/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/21 19:58:47 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// merge identification and insertion?
// more efficient way to tokenize + parse?
// sintax error implemetation!

// 1. get next token
// 2. quote identifier
// 	- if token contains quote, get next token until quote is closed
// 	- lots of quote edge cases
// 3. check for other special characters
// 	- heredoc
// 	- redirection and append
// 	- pipe
// 	- operator
// 	- word
// 4. insert node into AST
// (5. check for syntax errors)
// 6. repeat until EOF

#include "parser.h"

t_token *redirect(t_elem *stack)
{
	t_token *new;
	t_token *temp;

	new = create_token(stack->word);
	temp = new;
	temp->desc = desc_word(temp->word);
	stack = stack->next;
	temp->a = create_token(stack->word);
	temp = temp->a;
	temp->desc = desc_word(temp->word);
	return (new);
}

t_token	*simple_cmd(t_elem *top)
{
	t_token	*new;
	t_token	*temp;

	if (top->word == '>') // weird handling
		new = redirect(top);
	
	return (redirect(top));
}
