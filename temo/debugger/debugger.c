/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 18:41:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugger.h"

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
