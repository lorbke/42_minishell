/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:05:04 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/08 18:50:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
# define TOK_NEWLINE 11

typedef struct s_token
{
	char			*word;
	unsigned int	desc;
}	t_token;

typedef struct s_stack
{
	t_token			*token;
	struct s_stack	*next;
}	t_stack;

t_stack	*lexer_str_to_tokstack(char *str, char *seps, char *esc);

#endif
