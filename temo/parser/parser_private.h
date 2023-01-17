/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 18:24:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_PRIVATE_H
# define PARSER_PRIVATE_H

# include "lexer.h" // t_token, t_stack
# include "parser.h" // t_ast
// # include <stdio.h> // printf
// # include <string.h>
// # include <stdlib.h> // malloc, free
// # include <stdbool.h> // bool, true, false

t_ast	*rule_simple_cmd(t_stack **tokstack);
t_ast	*rule_comp_cmd(t_stack **tokstack);
t_ast	*rule_pipeline(t_stack **tokstack);
t_ast	*rule_and_or(t_stack **tokstack);
t_ast	*create_ast_node(t_token	*token);
t_ast	*left_append_ast(t_ast *main, t_ast *append);

#endif
