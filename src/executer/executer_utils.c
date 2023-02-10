/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:12:31 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/10 18:13:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer_private.h" // cmd_table
#include "../executer.h" // EXEC_* defines
#include "../mssignal.h" // init_signals
#include "parser.h" // t_ast
#include "lexer.h" // TOK_* defines
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // EOF
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <limits.h> // ARG_MAX
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history

extern char	**environ;

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
	cmd_table = malloc(sizeof(t_cmd_table));
	cmd_table->cmd = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ast && ast->token->desc == TOK_WORD)
	{
		cmd_table->cmd[i] = ast->token->word;
		ast = ast->left;
		i++;
	}
	cmd_table->cmd[i] = NULL;
	cmd_table->fd_in = STDIN_FILENO;
	cmd_table->fd_out = STDOUT_FILENO;
	return (cmd_table);
}

// @note newline bug when ctrl d

int	get_heredoc(char *limiter)
{
	int		fd[2];
	int		limiter_len;
	char	*line;
	int		status;
	pid_t	pid;

	mssignal_change_mode(MSSIG_NHDOC);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		mssignal_change_mode(MSSIG_HDOC);
		limiter_len = ft_strlen(limiter);
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strncmp(line, limiter, limiter_len + 1) == 0) // exit buildin will be added later
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		close(fd[1]);
		exit(EXEC_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		mssignal_change_mode(MSSIG_STD);
		exit_status_set(WEXITSTATUS(status));
		close(fd[1]);
	}
	return (fd[0]);
}

pid_t	exec_cmd(t_cmd_table *cmd_table)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	path = get_cmd_path(environ, cmd_table->cmd[0]);
	if (!path)
	{
		exit_status_set(EXEC_CMDNOTFOUND);
		return (-1);
	}
	pid = fork();
	if (pid != 0)
		return (pid);
	dup2(cmd_table->fd_in, STDIN_FILENO);
	dup2(cmd_table->fd_out, STDOUT_FILENO);
	status = execve(path, cmd_table->cmd, environ);
	close(cmd_table->fd_in);
	close(cmd_table->fd_out);
	exit(status);
}
