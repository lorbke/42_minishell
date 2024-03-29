/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 15:59:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_PARSER_H
# define PRIVATE_PARSER_H

# include "lexer.h" // t_token, t_stack
# include "parser.h" // t_ast
# include <stdbool.h> // bool

// utils
t_token	*create_token_empty(void);
t_ast	*create_ast_node(t_token *token);
bool	is_word(t_stack *token);
bool	is_redirect(t_stack *token);
t_ast	*append_left_ast(t_ast *main, t_ast *append);

// rules
t_ast	*rule_simple_cmd(t_stack **tokstack);
t_ast	*rule_pipeline(t_stack **tokstack);
t_ast	*rule_and_or(t_stack **tokstack);

// subshell
t_ast	*handle_subshell(t_stack **tokstack);

#endif
