/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:27:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:38:31 by lorbke           ###   ########.fr       */
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
#include "../quotes.h" // quotes_rmv_quotes_from_str
#include <stdio.h> // FILE
#include <readline/readline.h> // readline
#include <stdlib.h> // malloc, free
#include <unistd.h> // write, read, pipe, fork

#define DOC_PROMPT "> "

/**
 * It reads all the lines from a file descriptor and discards them
 * 
 * @param fd the file descriptor to read from
 */
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

/**
 * It reads lines from stdin until it finds a line that matches 
 * the given limiter, and writes all the
 * lines it reads to the given file descriptor
 * 
 * @param limiter the string that will be used to determine when 
 * the heredoc is over.
 * @param fd_write the file descriptor to write to.
 * 
 * @return the number of bytes written to the file descriptor.
 */
int	doc_heredoc(char *limiter, int fd_write)
{
	size_t	limiter_len;
	char	*line;

	quotes_rmv_quotes_from_str(limiter);
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

/**
 * It reads a line from stdin,
 * and writes it to the given file descriptor
 * 
 * @param unused the placeholder string that was passed to 
 * the completion function
 * @param fd_write the file descriptor to write to
 * 
 * @return The return value of the function is the return value 
 * of the last command executed.
 */
int	doc_completingdoc(__attribute__((unused)) char *placeholder, int fd_write)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, DOC_PROMPT, 2);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (ERR_SUCCESS);
	write(fd_write, " ", 1);
	line[ft_strlen(line) - 1] = 0;
	write(fd_write, line, ft_strlen(line));
	free(line);
	get_next_line(GNL_ERR);
	return (ERR_SUCCESS);
}

/**
 * It forks, and the child
 * executes the command, and the parent waits for the child to finish, and then
 * reads the output of the command from the pipe
 * 
 * @param pid the pid of the child process
 * @param fd_pipe the pipe file descriptors
 * @param exit_status the exit status of the child process
 * 
 * @return the documentation of the command.
 */
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
	else
		*exit_status = ERR_SUCCESS;
	if (!isatty(STDIN_FILENO))
		empty_fd(STDIN_FILENO);
	doc = ft_calloc(sizeof(char), ARG_MAX + 1);
	if (!doc)
		ft_perror_and_exit("case_parent: ft_calloc: malloc:");
	read(fd_pipe[0], doc, ARG_MAX);
	close(fd_pipe[0]);
	return (doc);
}

/**
 * It forks, and in the child process it calls the function 
 * passed as an argument, and in the parent
 * process it reads the output of the child process
 * 
 * @param doc_func a function that takes a string and a file descriptor, 
 * and writes the
 * @param lim the limit of the command, i.e. the first word of the command.
 * @param exit_status This is a pointer to a t_status variable. 
 * This variable will be set to ERR_GENERAL if there is an error.
 * 
 * @return A string containing the documentation for the command.
 */
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
