/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_doccer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 18:12:49 by lorbke           ###   ########.fr       */
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
#define CASE_COUNT 35
#define CASE_0 ""
#define CASE_1 "< in\n"
#define CASE_2 "cat |ls\n"
#define CASE_3 "echo a && eho b\n"
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
#define CASE_22 "echo 1<<lim| echo 2>out|| echo 3 | echo 4\n"
#define CASE_23 "echo ||\n"
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
#define CASE_34 "aSDasd(< in)echo hi\n"

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

char	*interpret_docs(t_stack *tokstack, char *input);

int	is_only_whitespace(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}

int	is_closed(char *str)
{
	char	*pipe;
	char	*and;

	if (is_only_whitespace(str))
		return (0);
	pipe = ft_strrchr(str, '|');
	and = ft_strrchr(str, '&');
	if (pipe && is_only_whitespace(pipe + 1))
		return (0);
	if (and && is_only_whitespace(and + 1))
		return (0);
	return (1);
}

void	doc_heredoc(char *limiter, int fd_write)
{
	int		limiter_len;
	char	*line;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, limiter, limiter_len + 1) == 0)
			break ;
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

void	doc_completingdoc(char *placeholder, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, " ", 1);
		line = readline("> ");
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (is_closed(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	doc_quotedoc(char *quote, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, "\n", 1);
		line = readline("> ");
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (ft_strchr(line, *quote))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

char	*get_doc(void (*doc_func)(char *, int), char *lim)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	*doc;

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		doc = ft_calloc(sizeof(char), ARG_MAX + 1);
		read(fd[0], doc, ARG_MAX);
		close(fd[0]);
		return (doc);
	}
	else
	{
		close(fd[0]);
		doc_func(lim, fd[1]);
		close(fd[1]);
		exit(0);
	}
}

char	*handle_unclosed_quote(char quote, char *input, t_stack *tokstack)
{
	char	*temp_str;

	free(tokstack->token->word);
	tokstack->token->word = get_doc(doc_quotedoc, &quote);
	temp_str = input;
	input = ft_strjoin(input, tokstack->token->word);
	free(temp_str);
	return (input);
}

char	*handle_incomplete_input(char *input, t_stack *tokstack)
{
	char	*temp_str;
	char	*doc;

	doc = get_doc(doc_completingdoc, NULL);
	tokstack->next = lexer_str_to_tokstack(doc, CMD_SEPS, CMD_ESCS);
	temp_str = input;
	input = ft_strjoin(input, doc);
	free(doc);
	input = interpret_docs(tokstack->next, input);
	return (input);
}

char	*interpret_docs(t_stack *tokstack, char *input)
{
	t_stack	*temp_stack;
	char	*doc;

	while (tokstack)
	{
		if (tokstack->token->desc == TOK_REDIR_HEREDOC && tokstack->next)
		{
			free(tokstack->token->word);
			tokstack->token->word
				= get_doc(doc_heredoc, tokstack->next->token->word);
		}
		temp_stack = tokstack;
		tokstack = tokstack->next;
	}
	if (temp_stack->token->desc == TOK_UNCLOSED_SQUOTE)
		input = handle_unclosed_quote('\'', input, temp_stack);
	else if (temp_stack->token->desc == TOK_UNCLOSED_DQUOTE)
		input = handle_unclosed_quote('\"', input, temp_stack);
	else if (temp_stack->token->desc == TOK_PIPE
		|| temp_stack->token->desc == TOK_AND
		|| temp_stack->token->desc == TOK_OR)
		input = handle_incomplete_input(input, temp_stack);
	return (input);
}

int	main(int argc, char **argv)
{
	char	*input = "echo 1<<lim| echo 2>out|| echo 3 |";
	t_stack	*tokstack;

	tokstack = lexer_str_to_tokstack(input, CMD_SEPS, CMD_ESCS);
	input = interpret_docs(tokstack, input);
	printf("input: %s\n", input);
	return (0);
}
