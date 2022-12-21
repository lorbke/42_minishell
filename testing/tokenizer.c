
#include "parser.h"

t_token	*create_token(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->word = word;
	new->desc = 100;
	new->a = NULL;
	new->b = NULL;
	return (new);
}

unsigned int	desc_word(char *word)
{
	if (*word == '|')
		return (2);
	if (*word != '\0')
		return (1);
	return (0);
}
