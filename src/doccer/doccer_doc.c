/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:27:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/23 01:46:26 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // utils
#include "libft.h" // ft_strrchr
#include "../mssignal.h" // mssignal_change_mode
#include "../minishell.h" // exit_status functions
#include "garbage_collector.h" // gc_free_all_garbage
#include "../expander.h" // expander_remove_quotes
#include <stdio.h> // FILE
#include <readline/readline.h> // readline
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, read, pipe, fork

#define DOC_PROMPT "> "

int	doc_heredoc(char *limiter, int fd_write)
{
	int		limiter_len;
	char	*line;

	expander_remove_quotes(limiter);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline(DOC_PROMPT);
		if (!line || ft_strncmp(line, limiter, limiter_len + 1) == 0)
			break ;
		write(fd_write, line, ft_strlen(line));
		write(fd_write, "\n", 1);
		free(line);
	}
	return (ERR_SUCCESS);
}

int	doc_completingdoc(char *placeholder, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, " ", 1);
		line = readline(DOC_PROMPT);
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (!is_only_whitespace(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (ERR_SUCCESS);
}

int	doc_quotedoc(char *quote, int fd_write)
{
	char	*line;
	char	*temp;

	while (1)
	{
		write(fd_write, "\n", 1);
		line = readline(DOC_PROMPT);
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		temp = ft_strchr(line, *quote);
		if (temp && ft_is_char_count_uneven(line, *quote))
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (!ft_is_char_count_uneven(line, *quote))
		return (ERR_SYNTAX);
	return (ERR_SUCCESS);
}

char	*get_doc(
	int (*doc_func)(char *, int), char *lim, t_status *exit_status)
{
	pid_t	pid;
	int		fd[2];
	char	*doc;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		mssignal_change_mode(MSSIG_EXEC);
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) != ERR_SUCCESS)
		{
			*exit_status = WEXITSTATUS(status);
			close(fd[0]);
			return (NULL);
		}
		doc = ft_calloc(sizeof(char), ARG_MAX + 1);
		read(fd[0], doc, ARG_MAX);
		close(fd[0]);
		return (doc);
	}
	else
	{
		mssignal_change_mode(MSSIG_DOC);
		close(fd[0]);
		status = doc_func(lim, fd[1]);
		close(fd[1]);
		gc_free_all_garbage();
		exit(status);
		return (NULL);
	}
}
