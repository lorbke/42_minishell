/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:34:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/20 17:35:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "lexer.h" // t_token, t_stack
# include "parser.h" // t_ast
# include "executer.h"
# include "executer/private_executer.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

void	debug_parser(t_ast *ast, t_stack *tokstack);
void	debug_lexer(t_stack *tokstack);
void	debug_message(char *message);
void	debug_cmd_table(t_cmd_table *cmd_table);

#endif
