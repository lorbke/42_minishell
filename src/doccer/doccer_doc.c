/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:27:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:42:47 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // utils
#include "libft.h" // ft_strrchr
#include <stdio.h> // FILE
#include <readline/readline.h> // readline
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, read, pipe, fork

void	doc_heredoc(char *limiter, int fd_write)
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
}

void	doc_completingdoc(char *placeholder, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, " ", 1);
		line = readline("> ");
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (is_closed(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	doc_quotedoc(char *quote, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, "\n", 1);
		line = readline("> ");
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (ft_strchr(line, *quote))
		{
			free(line);
			break ;
		}
		free(line);
	}
}

char	*get_doc(void (*doc_func)(char *, int), char *lim)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	*doc;

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		doc = ft_calloc(sizeof(char), ARG_MAX + 1);
		read(fd[0], doc, ARG_MAX);
		close(fd[0]);
		return (doc);
	}
	else
	{
		close(fd[0]);
		doc_func(lim, fd[1]);
		close(fd[1]);
		exit(0);
	}
}
