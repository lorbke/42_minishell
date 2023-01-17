/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 20:37:39 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"
#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// test cases
#define CASE_COUNT 25
#define CASE_0 ""
#define CASE_1 "< in\n"
#define CASE_2 "echo\n"
#define CASE_3 "echo hello ha\n"
#define CASE_4 "< in echo hi hi > out\n"
#define CASE_5 "< in1 < in2 < in3 echo hi hi > out1 > out2 > out4 hello hello\n"
#define CASE_6 "echo \"hi       hi\" hi\n"
#define CASE_7 "ec\"ho\" hi\n"
#define CASE_8 "ec\"'h'o\" hi\n"
#define CASE_9 "echo \'hi       hi\' hi\n"
#define CASE_10 "ec\'\"h\"o\' hi\n"
#define CASE_11 " echo   	  42 | cat -e\n"
#define CASE_12 "echo test | start -e | cat -e | cat -e | cat -e | end -e\n"
#define CASE_13 "| echo\n"
#define CASE_14 "echo |\n" // incomplete pipe case
#define CASE_15 " | \n"
#define CASE_16 "|\n"
#define CASE_17 "echo 1 && echo 2\n"
#define CASE_18 "echo 1 || echo 2\n"
#define CASE_19 "echo 1 && echo 2 && echo 3\n"
#define CASE_20 "echo 1 || echo 2 | echo 3\n"
#define CASE_21 "echo 1 | echo 2 && echo 3\n"
#define CASE_22 "echo 1 | echo 2 || echo 3 | echo 4\n"
#define CASE_23 "echo ||\n"
#define CASE_24 " || \n"

// colors for printf
# define RESET       "\033[0m"
# define BLACK       "\033[30m"        /* Black */
# define RED         "\033[31m"        /* Red */
# define GREEN       "\033[32m"        /* Green */
# define YELLOW      "\033[33m"        /* Yellow */
# define BLUE        "\033[34m"        /* Blue */
# define MAGENTA     "\033[35m"        /* Magenta */
# define CYAN        "\033[36m"        /* Cyan */
# define WHITE       "\033[37m"        /* White */
# define BOLDBLACK   "\033[1m\033[30m" /* Bold Black */
# define BOLDRED     "\033[1m\033[31m" /* Bold Red */
# define BOLDGREEN   "\033[1m\033[32m" /* Bold Green */
# define BOLDYELLOW  "\033[1m\033[33m" /* Bold Yellow */
# define BOLDBLUE    "\033[1m\033[34m" /* Bold Blue */
# define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
# define BOLDCYAN    "\033[1m\033[36m" /* Bold Cyan */
# define BOLDWHITE   "\033[1m\033[37m" /* Bold White */

static void	case_lexer(char **tests, char *seps, char *esc)
{
	char	*input;
	int		i;

	input = malloc(sizeof(char) * 100);
	i = 0;
	while (tests[i])
	{
		strcpy(input, tests[i]);
		debug_lexer(input, seps, esc);
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
		debug_parser(input, seps, esc);
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
	tests[18] = CASE_18;
	tests[19] = CASE_19;
	tests[20] = CASE_20;
	tests[21] = CASE_21;
	tests[22] = CASE_22;
	tests[23] = CASE_23;
	tests[24] = CASE_24;
	tests[25] = NULL;
	return (tests);
}

int	main(int argc, char *argv[])
{
	char	*seps = " \t\n\r";
	char	*esc = "\'\"()";
	char	**tests;

	if (argc != 2)
	{
		printf("usage: ./test [ all | lexer | parser ]\n");
		return (0);
	}
	tests = init_tests();
	if (!strncmp(argv[1], "all\0", 4))
	{
		case_lexer(tests, seps, esc);
		printf("\n\n\n");
		case_parser(tests, seps, esc);
	}
	else if (!strncmp(argv[1], "lexer\0", 10))
		case_lexer(tests, seps, esc);
	else if (!strncmp(argv[1], "parser\0", 7))
		case_parser(tests, seps, esc);
	else
		printf("usage: ./test [ all | lexer | parser ]\n");
	free(tests);
	return (0);
}
