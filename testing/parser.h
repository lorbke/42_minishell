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

char			*ft_strsep(char **stringp, const char *delim);

t_stack			*str_to_tokstack(char *str, char *seps);

void			print_tokstack(t_stack *head);
void			print_ast(t_ast *ast, int width);
// void			simple_print_ast(t_token *head);
// void			print_ast(t_token *head);

t_ast			*parse(t_stack	*toklist);

#endif
