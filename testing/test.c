/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/14 16:11:28 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// test cases
#define CASE_1 "< in"
#define CASE_2 "echo"
#define CASE_3 "echo hello ha"
#define CASE_4 "> out"
#define CASE_5 "echo hi > out"
#define CASE_6 "< in > out"
#define CASE_7 "< in echo hi hi > out"

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

void	case_tokenizer(void)
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(sizeof(char) * 100);
	strcpy(input, CASE_1);
	test_tokenizer(input, seps);
	strcpy(input, CASE_2);
	test_tokenizer(input, seps);
	strcpy(input, CASE_3);
	test_tokenizer(input, seps);
	strcpy(input, CASE_4);
	test_tokenizer(input, seps);
	strcpy(input, CASE_5);
	test_tokenizer(input, seps);
	strcpy(input, CASE_6);
	test_tokenizer(input, seps);
	strcpy(input, CASE_7);
	test_tokenizer(input, seps);
}

void	case_parser(void)
{
	char	*input;
	char	*seps = " \t\n\r";

	input = malloc(sizeof(char) * 100);
	strcpy(input, CASE_1);
	test_parser(input, seps);
	strcpy(input, CASE_2);
	test_parser(input, seps);
	strcpy(input, CASE_3);
	test_parser(input, seps);
	strcpy(input, CASE_4);
	test_parser(input, seps);
	strcpy(input, CASE_5);
	test_parser(input, seps);
	strcpy(input, CASE_6);
	test_parser(input, seps);
	strcpy(input, CASE_7);
	test_parser(input, seps);
}

int	main(int argc, char *argv[])
{
	char	*input;
	char	*seps = " \t\n\r";

	if (argc != 2)
	{
		printf("usage: ./test [all | tokenizer | parser]\n");
		return (0);
	}

	// test all
	if (!strncmp(argv[1], "all\0", 4))
	{
		case_tokenizer();
		case_parser();
	}
	// tokenizer test
	else if (!strncmp(argv[1], "tokenizer\0", 10))
		case_tokenizer();
	// simple_cmd test
	else if (!strncmp(argv[1], "parser\0", 7))
		case_parser();
	else
		printf("usage: ./test [all | tokenizer | parser]\n");
	return (0);
}
