/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:12:53 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 17:15:44 by lorbke           ###   ########.fr       */
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
