/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:16:59 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/14 14:52:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "executer_private.h" // exit_status_set
#include "../mssignal.h" // init_signals
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read

void	heredoc_big(char *limiter, int fd_write)
{
	int		limiter_len;
	char	*line;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, limiter, limiter_len + 1) == 0)
			break ;
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	close(fd_write);
}

void	heredoc_small(char *line, int fd_write)
{
	while (1)
	{
		line = readline("> ");
		if (*line)
			break ;
		add_history(line);
		free(line);
	}
	write(fd_write, line, ft_strlen(line));
	free(line);
	close(fd_write);
}

// @note newline bug when ctrl d
int	get_heredoc(void (*heredoc_type)(char *, int), char *limiter)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		mssignal_change_mode(MSSIG_HDOC);
		(*heredoc_type)(limiter, fd[1]);
		exit(EXEC_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		exit_status_set(WEXITSTATUS(status));
		close(fd[1]);
	}
	return (fd[0]);
}
