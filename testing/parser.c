/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/22 18:28:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// merge identification and insertion?
// more efficient way to tokenize + parse?
// syntax error implemetation!
// if statements early in the functions or at the end?


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

// double pointer to also update the original pointer in the calling function and reduce the stack
t_token *redirect(char **stack, char *seps)
{
	t_token	*new;

	new = create_token(ft_strsep(stack, seps));
	new->a = create_token(ft_strsep(stack, seps));
	// if new->a->word != REDIRECT -> syntax error
	return (new);
}

t_token	*simple_cmd(char *stack, char *seps)
{
	t_token	*new;
	t_token	*temp;

	if (*stack == '<') // proper peek function necessary
	{
		new = redirect(&stack, seps);
		new->b = create_token(ft_strsep(&stack, seps));
	}
	if (*stack == '>')
	{
		temp = new->b;
		new->b = redirect(&stack, seps);
		new->b->b = temp;
	}
	else
	{
		temp = new->b;
		while (temp->desc == 1)
		{
			temp->a = create_token(ft_strsep(&stack, seps));
			temp = temp->a;
		}
	}
	return (new);
}
