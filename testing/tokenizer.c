
#include "parser.h"

// maybe by using just a single pointer to the peek function and then calling ft_strsep in there, dirty solution though.
// char *peek_stack(char *stack, char *seps)

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
	if (word)
		new->desc = desc_word(word);
	new->a = NULL;
	new->b = NULL;
	return (new);
}

unsigned int	desc_word(char *word)
{
	if (*word == '<')
		return (4);
	if (*word == '>')
		return (3);
	if (*word == '|')
		return (2);
	if (*word != '\0')
		return (1);
	return (0);
}
