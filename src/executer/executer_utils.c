/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/15 19:07:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // cmd_table
#include "../executer.h" // EXEC_* defines
#include "../minishell.h" // process_input
#include "../mssignal.h" // mssignal_change_mode
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include "libft.h" // ft_strlen, ft_strncmp
#include <stdio.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read

extern char	**environ;

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
		cmd_table->cmd[i] = ast->token->word;
		ast = ast->left;
		i++;
	}
	cmd_table->cmd[i] = NULL;
	cmd_table->fd_in = STDIN_FILENO;
	cmd_table->fd_out = STDOUT_FILENO;
	cmd_table->fd_last = -1;
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

static pid_t	exec_subshell(t_cmd_table *cmd_table)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid != 0)
		return (pid);
	cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] = 0;
	status = process_input(cmd_table->cmd[0] + 1,
			cmd_table->fd_in, cmd_table->fd_out);
	exit(status);
}

// @note -1 as error sensible?
// @todo think of echo hi | cd .. case (directory is not changed) when implementing builtins
// @todo fix cat | ls, cat /dev/random | head -10 (cat is not killed)
// @todo fix echo hello | << lim cat (heredoc fd is overwritten)
pid_t	exec_cmd(t_cmd_table *cmd_table)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table));
	path = get_cmd_path(environ, cmd_table->cmd[0]);
	if (!path)
	{
		exit_status_set(EXEC_CMDNOTFOUND);
		return (-1);
	}
	pid = fork();
	if (pid != 0)
	{
		if (cmd_table->fd_in != STDIN_FILENO)
		{
			printf("(parent) closing fd_in of: %s\n", cmd_table->cmd[0]);
			close(cmd_table->fd_in);
		}
		if (cmd_table->fd_out != STDOUT_FILENO)
		{
			printf("(parent) closing fd_out of: %s\n", cmd_table->cmd[0]);
			close(cmd_table->fd_out);
		}
		if (cmd_table->fd_last != -1)
		{
			printf("(parent) closing fd_last of: %s\n", cmd_table->cmd[0]);
			close(cmd_table->fd_last);
		}
		return (pid);
	}
	mssignal_change_mode(MSSIG_NINTER);
	if (cmd_table->fd_in != STDIN_FILENO)
	{
		printf("(child) closing fd_in of: %s\n", cmd_table->cmd[0]);
		dup2(cmd_table->fd_in, STDIN_FILENO);
		close(cmd_table->fd_in);
	}
	if (cmd_table->fd_out != STDOUT_FILENO)
	{
		printf("(child) closing fd_out of: %s\n", cmd_table->cmd[0]);
		dup2(cmd_table->fd_out, STDOUT_FILENO);
		close(cmd_table->fd_out);
	}
	if (cmd_table->fd_last != -1)
	{
		printf("(child) closing fd_last of: %s\n", cmd_table->cmd[0]);
		close(cmd_table->fd_last);
	}
	status = execve(path, cmd_table->cmd, environ);
	exit(status);
}
