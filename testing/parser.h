/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/15 01:05:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is a recursive descent (RD) parser, as opposed to original bash's yacc
look-ahead left-to-right (LALR) parser. The RD parser was choosen because it
is a solution that is more interesting to me and because the current
implementation of the bash parser seems to be a relict of the past and even
bash's maintainers argue that it has weaknesses. */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* I have decided to use this format for the token identifiers instead of a 
bitmask like in the original bash. I don't see the benefits of a bitmask here,
since no memory can be saved due to each token having its own separate 
ident variable. 
Also, this format is useful for calling token-specific functions out of an array
of function pointers that is sorted according to the token ident numbers. */
# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_REDIR_IN 2
# define TOKEN_REDIR_OUT 3
# define TOKEN_REDIR_APPEND 4
# define TOKEN_REDIR_HEREDOC 5
# define TOKEN_SQUOTE 6
# define TOKEN_DQUOTE 7
# define TOKEN_SUBSHELL 8
# define TOKEN_AND 9
# define TOKEN_OR 10

typedef struct s_token
{
	char			*word;
	unsigned int	desc;
}	t_token;

typedef struct s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_stack
{
	t_token			*token;
	struct s_stack	*next;
}	t_stack;

// function is overly complicated and parenthesis logic is inconsistent
char			*ms_ft_strsep(
					char **stringp, const char *delim, const char *ignore);

t_stack			*str_to_tokstack(char *str, char *seps, char *esc);

void			print_tokstack(t_stack *head);
void			print_ast(t_ast *ast, int width);

t_ast			*parse(t_stack	*toklist);

#endif
