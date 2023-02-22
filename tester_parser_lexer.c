/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_parser_lexer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 17:54:27 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"
#include "executer.h"
#include "src/executer/private_executer.h"
#include "parser.h"
#include "lexer.h"
#include "libft.h"
#include "src/minishell.h"
#include "src/mssignal.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h>
#include <stdbool.h>

// lexer
#define CMD_SEPS " \t\n\r"
#define CMD_ESCS "\'\"()"

// test cases
#define CASE_COUNT 47
#define CASE_0 ""
#define CASE_1 "< in"
#define CASE_2 "cat |ls"
#define CASE_3 "echo a && eho b"
#define CASE_4 "/bin/echo hi hi > out\n"
#define CASE_5 "<in1<in2<in3 echo hi hi > out1> out2 >out4 hello hello\n"
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
#define CASE_17 "echo 1 \"&& echo\" 2\n"
#define CASE_18 "\"\n"
#define CASE_19 "\'\"\n"
#define CASE_20 "\"\"\n"
#define CASE_21 "echo \"1 | ec\'ho 2 &\"& echo 3\n"
#define CASE_22 "e\"ch\"o\n"
#define CASE_23 "\"echo\"\n"
#define CASE_24 "(echo hi)\n"
#define CASE_25 "(echo) hi\n"
#define CASE_26 "(echo) | echo hi \n"
#define CASE_27 "(echo | echo)\n"
#define CASE_28 "(echo |) echo\n"
#define CASE_29 "echo (| echo)\n"
#define CASE_30 "echo (&&) echo\n"
#define CASE_31 "(echo hi) > out\n"
#define CASE_32 "echo \"|(sdf)\n"
#define CASE_33 "(< in echo hi)\n"
#define CASE_34 "e\"ch\"o|echo\n"
#define CASE_35 "e\"ch\"o|(echo)\n"
#define CASE_36 "e\"ch\"o(|echo)\n"
#define CASE_37 "e\"ch\"(o|echo)\n"
#define CASE_38 "aSDasd(< in)echo hi\n"
#define CASE_39 "e\"adfasdf\"\"asdfadf\"\"(adfa\")"
#define CASE_40 "e\"adsssdf\"(asssssdsf\n"
#define CASE_41 "e\"adfasdf\"<<lim)\n"
#define CASE_42 "(echo (hi))\n"
#define CASE_43 "(echo (hi)\n"
#define CASE_44 "(echo (hi)))\n"
#define CASE_45 "adsfadfa \"\'     ddadddds\n"
#define CASE_46 "easdfadf\"adfasdf\n"

// colors for printf
#define RESET			"\033[0m"
#define BLACK			"\033[30m"			/* Black */
#define RED			"\033[31m"			/* Red */
#define GREEN			"\033[32m"			/* Green */
#define YELLOW			"\033[33m"			/* Yellow */
#define BLUE			"\033[34m"			/* Blue */
#define MAGENTA		"\033[35m"			/* Magenta */
#define CYAN			"\033[36m"			/* Cyan */
#define WHITE			"\033[37m"			/* White */
#define BOLDBLACK		"\033[1m\033[30m"	/* Bold Black */
#define BOLDRED		"\033[1m\033[31m"	/* Bold Red */
#define BOLDGREEN		"\033[1m\033[32m"	/* Bold Green */
#define BOLDYELLOW		"\033[1m\033[33m"	/* Bold Yellow */
#define BOLDBLUE		"\033[1m\033[34m"	/* Bold Blue */
#define BOLDMAGENTA	"\033[1m\033[35m"	/* Bold Magenta */
#define BOLDCYAN		"\033[1m\033[36m"	/* Bold Cyan */
#define BOLDWHITE		"\033[1m\033[37m"	/* Bold White */

// static char	*skip_until_after_char(char *str, char c)
// {
// 	while (*str && *str != c)
// 		str++;
// 	if (*str)
// 		str++;
// 	return (str);
// }

// static int	is_unclosed_quote(char *str)
// {
// 	char	quote;

// 	while (*str)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 		{
// 			quote = *str;
// 			str = skip_until_after_char(str + 1, *str);
// 			if (!*str && *(str - 1) != quote)
// 			{
// 				if (quote == '\'')
// 					return (1);
// 				else if (quote == '\"')
// 					return (2);
// 			}
// 		}
// 		else
// 			str++;
// 	}
// 	return (0);
// }

// static void	case_lexer(char **tests)
// {
// 	printf("%d\n", is_unclosed_quote("ech'o \"hi hi\" hi\n"));
// 	printf("%d\n", is_unclosed_quote("e\"adfasdf\""));
// 	printf("%d\n", is_unclosed_quote("e\"adfasdf\"\"asdfadf\"\"(adfa\""));
// 	printf("%d\n", is_unclosed_quote("echo hi hi hi\n"));
// 	printf("%d\n", is_unclosed_quote("ec\"ho\"\" h\"\"i hi hi\n"));
// }

static void	case_lexer(char **tests)
{
	char	*input;
	t_stack	*tokstack;
	int		i;

	input = malloc(sizeof(char) * 100);
	i = 0;
	while (tests[i])
	{
		printf(YELLOW "CASE %d: %s" RESET, i, tests[i]);
		strcpy(input, tests[i]);
		tokstack = lexer_str_to_tokstack(input);
		debug_lexer(tokstack);
		i++;
	}
	free(input);
}

static void	case_parser(char **tests)
{
	char	*input;
	t_ast	*ast;
	t_stack	*tokstack;
	int		i;

	input = malloc(sizeof(char) * 100);
	i = 0;
	while (tests[i])
	{
		printf(YELLOW "+++++++++++++++++++++++++++++\n" RESET);
		printf(YELLOW "CASE %d: %s" RESET, i, tests[i]);
		strcpy(input, tests[i]);
		tokstack = lexer_str_to_tokstack(input);
		ast = parser_tokstack_to_ast(&tokstack);
		debug_parser(ast, tokstack);
		i++;
	}
	free(input);
}

void	debug_executer(t_cmd_table *cmd_table)
{
	printf(BLUE "\n=========Executer=========\n" RESET);
	if (cmd_table)
	{
		while (*cmd_table->cmd)
		{
			printf("%s ", *cmd_table->cmd);
			cmd_table->cmd++;
		}
	}
	printf(BLUE "\n==========================\n\n\n" RESET);
}

// static void	case_executer(char **tests)
// {
// 	char		*input;
// 	t_ast		*ast;
// 	t_stack		*tokstack;
// 	t_cmd_table	*cmd_table;
// 	int			i;

// 	input = malloc(sizeof(char) * 100);
// 	i = 3;
// 	// while (tests[i])
// 	// {
// 		// printf(YELLOW "+++++++++++++++++++++++++++++\n" RESET);
// 		// printf(YELLOW "CASE %d: %s" RESET, i, tests[i]);
// 		strcpy(input, tests[i]);
// 		tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
// 		ast = parser_tokstack_to_ast(&tokstack);
// 		debug_parser(ast, tokstack);
// 		executer_exec_ast(ast, STDIN_FILENO, STDOUT_FILENO);
// 		// debug_executer(cmd_table);
// 		// free(cmd_table);
// 	// 	i++;
// 	// }
// 	free(input);
// }

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
	tests[25] = CASE_25;
	tests[26] = CASE_26;
	tests[27] = CASE_27;
	tests[28] = CASE_28;
	tests[29] = CASE_29;
	tests[30] = CASE_30;
	tests[31] = CASE_31;
	tests[32] = CASE_32;
	tests[33] = CASE_33;
	tests[34] = CASE_34;
	tests[35] = CASE_35;
	tests[36] = CASE_36;
	tests[37] = CASE_37;
	tests[38] = CASE_38;
	tests[39] = CASE_39;
	tests[40] = CASE_40;
	tests[41] = CASE_41;
	tests[42] = CASE_42;
	tests[43] = CASE_43;
	tests[44] = CASE_44;
	tests[45] = CASE_45;
	tests[46] = CASE_46;
	tests[47] = NULL;
	return (tests);
}

int	main(int argc, char *argv[])
{
	char	**tests;

	if (argc != 2)
	{
		printf("usage: ./test [ all | lexer | parser | executer ]\n");
		return (0);
	}
	tests = init_tests();
	if (!strncmp(argv[1], "all\0", 4))
	{
		case_lexer(tests);
		printf("\n\n\n");
		case_parser(tests);
		printf("\n\n\n");
		// case_executer(tests);
	}
	else if (!strncmp(argv[1], "lexer\0", 6))
		case_lexer(tests);
	else if (!strncmp(argv[1], "parser\0", 7))
		case_parser(tests);
	// else if (!strncmp(argv[1], "executer\0", 9))
	// 	case_executer(tests);
	else
		printf("usage: ./test [ all | lexer | parser | executer ]\n");
	free(tests);
	return (0);
}
