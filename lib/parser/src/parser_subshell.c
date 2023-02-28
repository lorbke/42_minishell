/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:12 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 15:57:58 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h" // utils
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros
#include "libft.h" // ft_strdup
#include <stdlib.h> // NULL
#include <stdbool.h> // bool, true, false

static bool	is_subshell_closed(char *str)
{
	int		depth;

	depth = 0;
	while (*str)
	{
		if (*str == '(')
			depth++;
		else if (*str == ')')
			depth--;
		str++;
	}
	if (!depth)
		return (true);
	return (false);
}

static bool	check_subshell_syntax(t_token *token)
{
	if (token->desc == TOK_SUBSHELL)
	{
		if (token->word[0] != '('
			|| token->word
			[ft_strlen(token->word) - 1] != ')'
			|| ft_strlen(token->word) < 3
			|| !is_subshell_closed(token->word))
		{
			return (true);
		}
	}
	return (false);
}

t_ast	*handle_subshell(t_stack **tokstack)
{
	t_ast	*new;

	if (!tokstack || !*tokstack || (*tokstack)->token->desc != TOK_SUBSHELL)
		return (NULL);
	if (check_subshell_syntax((*tokstack)->token))
		return (NULL);
	new = create_ast_node((*tokstack)->token);
	*tokstack = (*tokstack)->next;
	return (new);
}
