/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:40:18 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 18:23:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_private.h" // main header
#include "parser.h" // t_ast
#include "lexer.h" // t_token, t_stack, TOK_* macros

t_ast	*rule_comp_cmd(t_stack **tokstack)
{
	return (rule_simple_cmd(tokstack));
}
