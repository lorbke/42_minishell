#ifndef PARSER_H
#define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

/* This is a recursive descent (RD) parser, as opposed to original bash's yacc
look-ahead left-to-right (LALR) parser. The RD parser was choosen because it
is a solution that is more interesting to me and because the current
implementation of the bash parser seems to be a relict of the past and even
bash's maintainers argue that it has weaknesses. */

typedef struct s_token
{
	char			*word;
	unsigned int	desc;
	void			*a;
	void			*b;
}	t_token;

t_token			*create_token(char *word);
unsigned int	desc_word(char *word);
void			simple_print_ast(t_token *head);
void			print_ast(t_token *head);

#endif