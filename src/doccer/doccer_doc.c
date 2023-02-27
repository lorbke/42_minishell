/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:27:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 21:04:40 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_doccer.h" // utils
#include "libft.h" // ft_strrchr
#include "get_next_line.h"
#include "env.h" // g_env
#include "../utils.h" // env_free_sym_tab
#include "../mssignal.h" // mssignal_change_mode
#include "../minishell.h" // exit_status functions
#include "garbage_collector.h" // gc_free_all_garbage
#include "../expander.h" // expander_remove_quotes
#include <stdio.h> // FILE
#include <readline/readline.h> // readline
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, read, pipe, fork

#define DOC_PROMPT "> "

static void	empty_fd(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

int	doc_heredoc(char *limiter, int fd_write)
{
	int		limiter_len;
	char	*line;

	expander_remove_quotes(limiter);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, DOC_PROMPT, 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, limiter_len) == 0
				&& ft_strlen(line) - 1 == limiter_len))
			break ;
		write(fd_write, line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	get_next_line(GNL_ERR);
	return (ERR_SUCCESS);
}

int	doc_completingdoc(char *placeholder, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, " ", 1);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, DOC_PROMPT, 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
		write(fd_write, line, ft_strlen(line));
		if (!is_only_whitespace(line))
		{
			free(line);
			break ;
		}
		free(line);
	}
	get_next_line(GNL_ERR);
	return (ERR_SUCCESS);
}

int	doc_quotedoc(char *quote, int fd_write)
{
	char	*line;
	char	*temp;

	while (1)
	{
		write(fd_write, "\n", 1);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, DOC_PROMPT, 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line[ft_strlen(line) - 1] = 0;
		write(fd_write, line, ft_strlen(line));
		temp = ft_strchr(line, *quote);
		if (temp && ft_is_char_count_uneven(line, *quote))
		{
			free(line);
			break ;
		}
		free(line);
	}
	get_next_line(GNL_ERR);
	return (ERR_SUCCESS);
}

static char	*case_parent(pid_t pid, int fd_pipe[2], t_status *exit_status)
{
	char	*doc;
	int		status;

	mssignal_change_mode(MSSIG_EXEC);
	close(fd_pipe[1]);
	waitpid(pid, &status, 0);
	mssignal_change_mode(MSSIG_INTER);
	if (WEXITSTATUS(status) != ERR_SUCCESS)
	{
		*exit_status = WEXITSTATUS(status);
		close(fd_pipe[0]);
		return (NULL);
	}
	if (!isatty(STDIN_FILENO))
		empty_fd(STDIN_FILENO);
	doc = ft_calloc(sizeof(char), ARG_MAX + 1);
	if (!doc)
		ft_perror_and_exit("case_parent: ft_calloc: malloc:");
	read(fd_pipe[0], doc, ARG_MAX);
	close(fd_pipe[0]);
	return (doc);
}

char	*get_doc(
	int (*doc_func)(char *, int), char *lim, t_status *exit_status)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	if (fd[0] == RETURN_ERROR || fd[1] == RETURN_ERROR || pid == RETURN_ERROR)
	{
		*exit_status = ERR_GENERAL;
		return (NULL);
	}
	if (pid == 0)
	{
		mssignal_change_mode(MSSIG_DOC);
		close(fd[0]);
		status = doc_func(lim, fd[1]);
		close(fd[1]);
		env_free_sym_tab(g_sym_table);
		gc_free_all_garbage();
		exit(status);
		return (NULL);
	}
	else
		return (case_parent(pid, fd, exit_status));
}
