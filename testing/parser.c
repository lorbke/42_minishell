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

// quotes single tokens or big token?
// merge identification and insertion?
// backlink to parent node for the ast?

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



int	main(void)
{
	char	*input;
	char	*seps = " \t\n\r";
	t_elem	*head;

	input = malloc(100);
	strcpy(input, "ls	-l -a |\necho\rhello");
	head = create_input_stack(input, seps);
	print_token_stack(head);
	return (0);
}
