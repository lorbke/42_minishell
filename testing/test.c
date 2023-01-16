/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/16 17:57:40 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// test cases
#define CASE_COUNT 18
#define CASE_0 ""
#define CASE_1 "< in"
#define CASE_2 "echo"
#define CASE_3 "echo hello ha"
#define CASE_4 "< in echo hi hi > out"
#define CASE_5 "< in1 < in2 < in3 echo hi hi > out1 > out2 > out4 hello hello"
#define CASE_6 "echo \"hi       hi\" hi"
#define CASE_7 "ec\"ho\" hi"
#define CASE_8 "ec\"'h'o\" hi"
#define CASE_9 "echo \'hi       hi\' hi"
#define CASE_10 "ec\'\"h\"o\' hi"
#define CASE_11 " echo 42 | cat -e"
#define CASE_12 "echo test | cat -e | cat -e | cat -e | cat -e | cat -e"
#define CASE_13 "| echo"
#define CASE_14 "echo |"
#define CASE_15 " | "
#define CASE_16 "|"
#define CASE_17 "echo | cat -e | > out"

// colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static void	test_tokenizer(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;

	tokstack = str_to_tokstack(input, seps, esc);
	print_tokstack(tokstack);
}

static void	test_parser(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = str_to_tokstack(input, seps, esc);
	ast = parse(tokstack);
	print_ast(ast, 0);
}

static void	case_tokenizer(char **tests, char *seps, char *esc)
{
	char	*input;
	int		i;

	input = malloc(sizeof(char) * 100);
	i = 0;
	while (tests[i])
	{
		strcpy(input, tests[i]);
		test_tokenizer(input, seps, esc);
		printf(YELLOW "CASE %d\n\n" RESET, i);
		i++;
	}
	free(input);
}

static void	case_parser(char **tests, char *seps, char *esc)
{
	char	*input;
	int		i;

	input = malloc(sizeof(char) * 100);
	i = 0;
	while (tests[i])
	{
		strcpy(input, tests[i]);
		test_parser(input, seps, esc);
		printf(YELLOW "CASE %d\n\n" RESET, i);
		i++;
	}
	free(input);
}

static char	**init_tests(void)
{
	char	**tests;

	tests = malloc(sizeof(char *) * CASE_COUNT + 1);
	tests[0] = CASE_0;
	tests[1] = CASE_1;
	tests[2] = CASE_2;
	tests[3] = CASE_3;
	tests[4] = CASE_4;
	tests[5] = CASE_5;
	tests[6] = CASE_6;
	tests[7] = CASE_7;
	tests[8] = CASE_8;
	tests[9] = CASE_9;
	tests[10] = CASE_10;
	tests[11] = CASE_11;
	tests[12] = CASE_12;
	tests[13] = CASE_13;
	tests[14] = CASE_14;
	tests[15] = CASE_15;
	tests[16] = CASE_16;
	tests[17] = CASE_17;
	tests[18] = NULL;
	return (tests);
}

int	main(int argc, char *argv[])
{
	char	*seps = " \t\n\r";
	char	*esc = "\'\"()";
	char	**tests;

	if (argc != 2)
	{
		printf("usage: ./test [ all | tokenizer | parser ]\n");
		return (0);
	}
	tests = init_tests();
	if (!strncmp(argv[1], "all\0", 4))
	{
		case_tokenizer(tests, seps, esc);
		printf("\n\n\n");
		case_parser(tests, seps, esc);
	}
	else if (!strncmp(argv[1], "tokenizer\0", 10))
		case_tokenizer(tests, seps, esc);
	else if (!strncmp(argv[1], "parser\0", 7))
		case_parser(tests, seps, esc);
	else
		printf("usage: ./test [ all | tokenizer | parser ]\n");
	free(tests);
	return (0);
}
