/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 18:35:46 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "parser_private.h"

void	debug_tokenizer(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;

	tokstack = str_to_tokstack(input, seps, esc);
	print_tokstack(tokstack);
}

void	debug_parser(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = str_to_tokstack(input, seps, esc);
	ast = parse(&tokstack);
	print_ast(ast, 0);
	print_tokstack(tokstack);
	if (tokstack)
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET, tokstack->token->word);
	else
		printf(GREEN "minishell: syntax valid!\n" RESET);
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
