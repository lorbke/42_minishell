
#include "parser.h"

int	main(void)
{
	char	*input;
	char	*seps = " \t\n\r";
	t_elem	*head;

	input = malloc(100);
	strcpy(input, "ls	-l -a |\necho\rhello");
	head = create_input_stack(input, seps);
	print_token_stack(head);
	return (0);
}
