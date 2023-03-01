/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:14:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/01 00:23:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_debugger.h" // main header
#include "../debugger.h" // DEBUG macro
#include "../executer/private_executer.h" // t_cmd_table
#include "lexer.h" // lexer functions
#include "parser.h" // parser functions
#include "env.h" // env_is_var_value
#include <stdio.h> // printf
#include <string.h> // strlen

void	debug_lexer(t_stack *tokstack)
{
	if (!env_is_var_value(DEBUG, "1"))
		return ;
	printf(BLUE "\n=========Token Stack=========\n" RESET);
	print_tokstack(tokstack);
	printf(BLUE "\n=============================" RESET);
	printf("\n\n\n");
}

void	debug_message(char *message, int type)
{
	if (!env_is_var_value(DEBUG, "1"))
		return ;
	if (type == 0)
		printf(BLUE "%s" RESET, message);
	else if (type == 1)
		printf(YELLOW "%s" RESET, message);
}

void	debug_cmd_table(t_cmd_table *cmd_table)
{
	int			i;

	if (!env_is_var_value(DEBUG, "1"))
		return ;
	printf(YELLOW "executing command table....\n" RESET);
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
	printf(YELLOW "....................output:\n" RESET);
}

void	debug_parser(t_ast *ast)
{
	if (!env_is_var_value(DEBUG, "1"))
		return ;
	printf(BLUE "\n=========Abstract Syntax Tree=========\n" RESET);
	print_ast(ast, 0);
	printf(BLUE "======================================" RESET);
	printf("\n\n\n");
}
