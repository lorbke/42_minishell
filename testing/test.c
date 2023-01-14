/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/14 18:10:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// test cases
#define CASE_COUNT 8
#define CASE_1 "< in"
#define CASE_2 "echo"
#define CASE_3 "echo hello ha"
#define CASE_4 "> out"
#define CASE_5 "echo hi > out"
#define CASE_6 "< in > out"
#define CASE_7 "< in echo hi hi > out"
#define CASE_8 "echo hi && cat > out"

void	test_tokenizer(char *input, char *seps)
{
	t_stack	*tokstack;

	tokstack = str_to_tokstack(input, seps);
	print_tokstack(tokstack);
}

void	test_parser(char *input, char *seps)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = str_to_tokstack(input, seps);
	ast = parse(tokstack);
	print_ast(ast, 0);
}

void	case_tokenizer(char **tests)
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(sizeof(char) * 100);
	while (*tests)
	{
		strcpy(input, *tests);
		test_tokenizer(input, seps);
		tests++;
	}
}

void	case_parser(char **tests)
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(sizeof(char) * 100);
	while (*tests)
	{
		strcpy(input, *tests);
		test_parser(input, seps);
		tests++;
	}
}

char	**init_tests(void)
{
	char	**tests;

	tests = malloc(sizeof(char *) * CASE_COUNT + 1);
	tests[0] = CASE_1;
	tests[1] = CASE_2;
	tests[2] = CASE_3;
	tests[3] = CASE_4;
	tests[4] = CASE_5;
	tests[5] = CASE_6;
	tests[6] = CASE_7;
	tests[7] = CASE_8;
	tests[8] = NULL;
	return (tests);
}

int	main(int argc, char *argv[])
{
	char	*input;
	char	*seps = " \t\n\r";
	char	**tests;

	if (argc != 2)
	{
		printf("usage: ./test [ all | tokenizer | parser ]\n");
		return (0);
	}

	tests = init_tests();
	if (!strncmp(argv[1], "all\0", 4))
	{
		case_tokenizer(tests);
		printf("\n\n\n");
		case_parser(tests);
	}
	else if (!strncmp(argv[1], "tokenizer\0", 10))
		case_tokenizer(tests);
	else if (!strncmp(argv[1], "parser\0", 7))
		case_parser(tests);
	else
		printf("usage: ./test [ all | tokenizer | parser ]\n");
	return (0);
}
