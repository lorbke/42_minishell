/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:04:42 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 17:41:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// every function gets the stack as input and returns a sub-ast that is then connected to the main ast

// due to easier usage and because the additional memory and run time are negligible, 
// the token stack will be represented by a token_list instead of just a string

// free the tokstack after parsing

// rule_all was skipped because identifying a newline is probably not needed and will be treated as a delim during tokenization

static void	free_tokstack(t_stack *tokstack)
{
	t_stack	*temp;

	while (tokstack->next)
	{
		temp = tokstack;
		tokstack = tokstack->next;
		free(tokstack);
	}
}

t_ast	*parse(t_stack	**tokstack)
{
	t_ast	*ast;
	t_stack	*temp;

	temp = *tokstack;
	ast = rule_and_or(tokstack);
	// free_tokstack(temp);
	return (ast);
}
