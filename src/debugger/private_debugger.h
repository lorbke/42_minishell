/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private_debugger.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:31:22 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 15:36:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_DEBUGGER_H
# define PRIVATE_DEBUGGER_H

# include "lexer.h" // t_token, t_stack
# include "parser.h" // t_ast

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

void	print_ast(t_ast *ast, int width);
void	print_tokstack(t_stack *head);

#endif
