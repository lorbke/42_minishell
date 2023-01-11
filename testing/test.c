
#include "parser.h"

// tokenizer test
void	test_tokenizer(char *input, char *seps)
{
	t_stack	*tokstack;

	tokstack = str_to_token_stack(input, seps);
	print_token_stack(tokstack);
}

void	test_parser(char *input)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = str_to_token_stack(input, " \t\n\r");
	ast = parse(tokstack);
	print_ast(ast, 0);
}

int	main(int argc, char *argv[])
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(sizeof(char) * 100);
	strcpy(input, "< in cat");
	test_parser(input);
	return (0);
}
