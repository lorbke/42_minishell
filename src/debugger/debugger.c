/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/20 17:38:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger_private.h" // main header
#include "../debugger.h" // DEBUG macro
#include "lexer.h" // lexer functions
#include "parser.h" // parser functions
#include <stdio.h> // printf
#include <string.h> // strlen
#include <termios.h> // termios struct

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

/* Debug function to print the terminal settings. */
void	debug_print_termios(struct termios *termios)
{
	if (!DEBUG)
		return ;
	printf("termios:\n");
	printf("	input mode: %lx\n", termios->c_iflag);
	printf("	output mode: %lx\n", termios->c_oflag);
	printf("	control mode: %lx\n", termios->c_cflag);
	printf("	local mode: %lx\n", termios->c_lflag);
	printf("	control characters: %hhu\n", termios->c_cc[VQUIT]);
	printf("	input speed: %lu\n", termios->c_ispeed);
	printf("	output speed: %lu\n", termios->c_ospeed);
}

void	debug_lexer(t_stack *tokstack)
{
	if (!DEBUG)
		return ;
	print_tokstack(tokstack);
}

void	debug_parser(t_ast *ast, t_stack *tokstack)
{
	if (!DEBUG)
		return ;
	print_ast(ast, 0);
	if (tokstack)
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET, tokstack->token->word);
	else
		printf(GREEN "minishell: syntax valid!\n" RESET);
}
