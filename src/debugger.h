/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:34:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 18:20:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "lexer.h" // t_token, t_stack
# include "parser.h" // t_ast
# include "executer.h"
# include "executer/private_executer.h"

# define DEBUG "DEBUG"

// colors for printf
# define RESET       "\033[39;49m"
# define BLACK       "\033[30m"        /* Black */
# define RED         "\033[31m"        /* Red */
# define GREEN       "\033[32m"        /* Green */
# define YELLOW      "\033[33m"        /* Yellow */
# define BLUE        "\033[34m"        /* Blue */
# define MAGENTA     "\033[35m"        /* Magenta */
# define CYAN        "\033[36m"        /* Cyan */
# define WHITE       "\033[37m"        /* White */
# define BOLDBLACK   "\033[1m\033[30m" /* Bold Black */
# define BOLDRED     "\033[1m\033[31m" /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m" /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m" /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m" /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m" /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m" /* Bold White */

void	debug_parser(t_ast *ast);
void	debug_lexer(t_stack *tokstack);
void	debug_message(char *message, int type);
void	debug_cmd_table(t_cmd_table *cmd_table);

#endif
