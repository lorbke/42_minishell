/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:22:41 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 17:48:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is a recursive descent (RD) parser, as opposed to original bash's yacc
look-ahead left-to-right (LALR) parser. The RD parser was chosen because it
is a solution that is more interesting to me and because the current
implementation of the bash parser seems to be a relict of the past and even
bash's maintainers argue that it has weaknesses. */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h> // printf
# include <string.h>
# include <stdlib.h> // malloc, free
# include <stdbool.h> // bool, true, false

//
// wildcards and variables are identified as words and not handled in the parser
//
/* I have decided to use this format for the token identifiers instead of a 
bitmask like in the original bash. The benefits of a bitmask only apply if a
token can have multiple properties, which isn't the case in this implementation.
Also, this format is useful for calling token-specific functions out of an array
of function pointers that is arranged according to the token ident numbers,
which will be useful during the execution phase. */
# define TOK_WORD 0
# define TOK_PIPE 1
# define TOK_REDIR_IN 2
# define TOK_REDIR_OUT 3
# define TOK_REDIR_HEREDOC 4
# define TOK_REDIR_APPEND 5
# define TOK_SQUOTE 6
# define TOK_DQUOTE 7
# define TOK_SUBSHELL 8
# define TOK_AND 9
# define TOK_OR 10

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
char	*ms_ft_strsep(
			char **stringp, const char *delim, const char *ignore);

t_stack	*str_to_tokstack(char *str, char *seps, char *esc);

void	print_tokstack(t_stack *head);
void	print_ast(t_ast *ast, int width);

t_ast	*parse(t_stack	**tokstack);

//rules
t_ast	*rule_simple_cmd(t_stack **tokstack);
t_ast	*rule_comp_cmd(t_stack **tokstack);
t_ast	*rule_pipeline(t_stack **tokstack);
t_ast	*rule_and_or(t_stack **tokstack);

// utils
t_ast	*create_ast_node(t_token	*token);
t_ast	*left_append_ast(t_ast *main, t_ast *append);

#endif
