
#include "parser.h"

void	print_token_stack(t_elem *head)
{
	while (head)
	{
		printf("%s->", head->word);
		head = head->next;
	}
	printf("\n");
}

void	simple_print_ast(t_token *head)
{
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
	head = head->a;
	printf("%s->", head->word);
}

void	print_ast(t_token *head)
{
	t_token	*temp;
	int		width_a;
	int		width_b;

	temp = create_token(NULL);
	width_a = 60;
	width_b = 5;
	printf("\n");
	// while (head)
	// {
	// 	if (head && head->word)
	// 		printf("%*s", width_a, head->word);
	// 	if (temp && temp->word)
	// 		printf("%*s", width_b, temp->word);
	// 	printf("\n");
	// 	temp = head->b;
	// 	head = head->a;
	// 	width_a -= 5;
	// 	width_b += 5;
	// }
	printf("\n");
}
