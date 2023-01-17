/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/17 17:42:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

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
