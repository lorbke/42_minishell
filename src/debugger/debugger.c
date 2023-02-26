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
#include "../executer/private_executer.h" // t_cmd_table
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

void	debug_lexer(t_stack *tokstack)
{
	if (!DEBUG)
		return ;
	printf(BLUE "\n=========Token Stack=========\n" RESET);
	print_tokstack(tokstack);
	printf(BLUE "\n=============================" RESET);
	printf("\n\n\n");
}

void	debug_message(char *message)
{
	if (!DEBUG)
		return ;
	printf(BLUE "%s" RESET, message);
}

void	debug_cmd_table(t_cmd_table *cmd_table)
{
	int			i;

	if (!DEBUG)
		return ;
	printf(BLUE "\nexecuting command table....\n" RESET);
	if (!cmd_table)
	{
		printf("     [NULL]\n");
		return ;
	}
	i = 0;
	printf("     command:");
	while (cmd_table->cmd[i])
	{
		printf(" [%s]", cmd_table->cmd[i]);
		i++;
	}
	printf("\n");
	printf("     in file descriptor:  %d\n", cmd_table->fd_in[0]);
	printf("       precedence level:  %d\n", cmd_table->fd_in[1]);
	printf("     out file descriptor: %d\n", cmd_table->fd_out[0]);
	printf("       precedence level:  %d\n", cmd_table->fd_out[1]);
	printf(BLUE "....................output:\n" RESET);
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
