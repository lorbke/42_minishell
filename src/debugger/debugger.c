/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 14:48:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_debugger.h" // main header
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
		printf("[ %*i ]->", (int)strlen(temp->token->word), temp->token->desc);
		temp = temp->next;
	}
}

void	print_ast(t_ast *ast, int width)
{
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
	printf(BLUE "\n=========Termios=========\n" RESET);
	printf("input mode:    %lx\n", termios->c_iflag);
	printf("output mode:   %lx\n", termios->c_oflag);
	printf("control mode:  %lx\n", termios->c_cflag);
	printf("local mode:    %lx\n", termios->c_lflag);
	printf("control chars: %hhu\n", termios->c_cc[VQUIT]);
	printf("input speed:   %lu\n", termios->c_ispeed);
	printf("output speed:  %lu\n", termios->c_ospeed);
	printf(BLUE "=========================" RESET);
	printf("\n\n\n");
}

void	debug_lexer(t_stack *tokstack)
{
	if (!DEBUG)
		return ;
	printf(BLUE "\n=========Token Stack=========\n" RESET);
	print_tokstack(tokstack);
	printf(BLUE "\n=============================" RESET);
	printf("\n\n\n");
}

void	debug_parser(t_ast *ast, t_stack *tokstack)
{
	if (!DEBUG)
		return ;
	printf(BLUE "\n=========Abstract Syntax Tree=========\n" RESET);
	print_ast(ast, 0);
	if (tokstack)
		printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET, tokstack->token->word);
	else
		printf(GREEN "minishell: syntax valid!\n" RESET);
	printf(BLUE "======================================" RESET);
	printf("\n\n\n");
}
