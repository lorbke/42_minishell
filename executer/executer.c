/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:57:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/23 17:06:22 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"
#include "parser.h"
#include "lexer.h"
#include <unistd.h>
#include <fcntl.h> // open
#include <stdlib.h> // malloc

// func execute cmd_table
	// expansion
	// fork
	// execve

// func create_cmd_table
t_cmd_table	*create_cmd_table(t_ast *ast)
{
	t_cmd_table	*cmd_table;
	t_ast		*temp;
	int			i;

	temp = ast;
	i = 0;
	while (temp && temp->token->desc == TOK_WORD)
	{
		temp = temp->left;
		i++;
	}
	cmd_table = (t_cmd_table *)malloc(sizeof(t_cmd_table));
	cmd_table->cmd = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ast && ast->token->desc == TOK_WORD)
	{
		cmd_table->cmd[i] = ast->token->word;
		ast = ast->left;
		i++;
	}
	cmd_table->cmd[i] = NULL;
	cmd_table->fd_in = 0;
	cmd_table->fd_out = 1;
	return (cmd_table);
}

// func func_pointer_init

// func for every (almost) toktype
// t_cmd_table	*exec_redir_out(t_ast *ast)
// {
// 	t_cmd_table	*cmd_table;

// 	cmd_table = exec_cmd(ast->left);
// 	cmd_table->fd_out = open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	return (cmd_table);
// }

// t_cmd_table	*exec_cmd(t_ast *ast)
// {
// 	t_cmd_table	*cmd_table;

// 	cmd_table = create_cmd_table(ast);
// 	return (cmd_table);
// }
