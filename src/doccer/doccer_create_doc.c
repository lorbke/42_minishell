/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_create_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:14:04 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 17:07:42 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" // t_ast
#include "../executer.h" // t_status
#include "../mssignal.h" // mssignal_change_mode
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h> // open, O_CREAT, O_WRONLY, O_TRUNC

#define DOCC_DIR "/tmp/heredoc"

void	doc_heredoc(char *limiter, int fd_write)
{
	int		limiter_len;
	char	*line;

	limiter_len = strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line || strncmp(line, limiter, limiter_len + 1) == 0)
			break ;
		write(fd_write, line, strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
}

void	doc_unclosed(char *line, int fd_write)
{
	while (1)
	{
		line = readline("> ");
		if (*line)
			break ;
		free(line);
	}
	write(fd_write, line, strlen(line));
	free(line);
}

// @note newline bug when ctrl d
t_status	create_doc(t_ast *ast, void (*doc_type)(char *, int))
{
	pid_t		pid;
	int			fd;
	int			status;
	char		*limiter;
	char		*suffix;

	mssignal_change_mode(MSSIG_EXEC);
	suffix = ft_itoa((int)&ast->token->word);
	limiter = ast->token->word;
	ast->token->word = ft_strjoin(DOCC_DIR, suffix);
	free(suffix);
	fd = open(ast->token->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (EXEC_GENERALERR);
	pid = fork();
	if (pid > 0)
	{
		close(fd);
		waitpid(pid, &status, 0);
		return ((t_status)WEXITSTATUS(status));
	}
	mssignal_change_mode(MSSIG_HDOC);
	(*doc_type)(limiter, fd);
	close(fd);
	exit(EXEC_SUCCESS);
}
