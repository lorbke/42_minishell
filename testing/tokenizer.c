
#include "parser.h"

t_elem *create_input_stack(char *input, char *seps)
{
	t_elem	*head;
	t_elem 	*temp;

	head = malloc(sizeof(t_elem));
	head->word = ft_strsep(&input, seps);
	temp = head;
	while (*input)
	{
		temp->next = malloc(sizeof(t_elem));
		temp = temp->next;
		temp->word = ft_strsep(&input, seps);
	}
	temp->next = NULL;
	return (head);
}

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
