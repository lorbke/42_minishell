
#include "parser.h"

t_token *redirect(t_elem *head);
t_token	*simple_cmd(t_elem *head);

int	main(void)
{
	char	*input;
	char	*seps = " \t\n\r";
	t_elem	*stack;

	input = malloc(100);
	strcpy(input, "> in | echo hi");
	stack = create_input_stack(input, seps);
	simple_print_ast(simple_cmd(stack));
	return (0);
}
