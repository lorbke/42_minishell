/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/16 14:52:27 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read

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
	cmd_table->fd_in = STDIN_FILENO;
	cmd_table->fd_out = STDOUT_FILENO;
	return (cmd_table);
}

void	wait_pid_and_set_exit(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status_set(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		exit_status_set(EXEC_SIGNAL + WTERMSIG(status));
		if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit: 3", 7);
		write(STDOUT_FILENO, "\n", 1);
	}
}
