/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 20:36:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger_private.h" // main header
#include "lexer.h" // lexer functions
#include "parser.h" // parser functions
#include <stdio.h> // printf
#include <string.h> // strlen

void	print_tokstack(t_stack *head)
{
	t_stack	*temp;

	temp = head;
	printf(BLUE "\n=========Token Stack=========\n" RESET);
	printf("stack: ");
	while (head)
	{
		printf("[ %s ]->", head->token->word);
		head = head->next;
	}
	printf("\n");
	printf("ident: ");
	while (temp)
	{
		printf("[ %*u ]->", strlen(temp->token->word), temp->token->desc);
		temp = temp->next;
	}
	printf("\n");
}

void	print_ast(t_ast *ast, int width)
{
	if (!width)
		printf(BLUE "\n=========Abstract Syntax Tree=========\n" RESET);
	if (!ast)
		return ;
	print_ast(ast->right, width + 7);
	printf("%*s\n", width, ast->token->word);
	print_ast(ast->left, width + 7);
}

void	debug_lexer(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;

	tokstack = lexer_str_to_tokstack(input, seps, esc);
	print_tokstack(tokstack);
}

void	debug_parser(char *input, char *seps, char *esc)
{
	t_stack	*tokstack;
	t_ast	*ast;

	tokstack = lexer_str_to_tokstack(input, seps, esc);
	ast = parse(&tokstack);
	print_ast(ast, 0);
	print_tokstack(tokstack);
	if (tokstack)
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET, tokstack->token->word);
	else
		printf(GREEN "minishell: syntax valid!\n" RESET);
}
