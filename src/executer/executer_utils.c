/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 14:47:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <stdio.h> // printf
#include <sys/errno.h> // errno macros
#include <string.h> // strerror

void	print_error(t_status exit_status, char *error_loc)
{
	if (exit_status == ERR_CMDNOTFOUND)
		printf("%s: %s: command not found\n", SHELL_NAME, error_loc);
	else if (exit_status >= ERR_SIGNAL && exit_status <= ERR_SIGNAL + 9)
		return ;
	else if (exit_status != ERR_SUCCESS
		&& exit_status != ERR_SYNTAXERR)
		printf("%s: %s: %s\n", SHELL_NAME, error_loc, strerror(errno));
}

t_cmd_table	*create_cmd_table(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	t_ast		*temp;
	int			i;

	temp = ast;
	i = 0;
	while (temp && (temp->token->desc == TOK_WORD
			|| temp->token->desc == TOK_SUBSHELL))
	{
		temp = temp->left;
		i++;
	}
	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ast && (ast->token->desc == TOK_WORD
			|| ast->token->desc == TOK_SUBSHELL))
	{
		cmd_table->cmd[i++] = ast->token->word;
		ast = ast->left;
	}
	cmd_table->cmd[i] = NULL;
	cmd_table->fd_in[0] = STDIN_FILENO;
	cmd_table->fd_out[0] = STDOUT_FILENO;
	cmd_table->fd_in[1] = FDLVL_STD;
	cmd_table->fd_out[1] = FDLVL_STD;
	return (cmd_table);
}
