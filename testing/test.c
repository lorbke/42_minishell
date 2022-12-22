
#include "parser.h"

t_token *redirect(char *stack, char *seps);
t_token	*simple_cmd(char *stack, char *seps);

int	main(void)
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(100);
	strcpy(input, "< in cat -l -a -b");
	simple_print_ast(simple_cmd(input, seps));
	return (0);
}
