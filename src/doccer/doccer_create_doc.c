/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_create_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:14:04 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/18 19:06:46 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" // t_ast
#include "../minishell.h" // t_status, ERR_* defines
#include "../mssignal.h" // mssignal_change_mode
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h> // open, O_CREAT, O_WRONLY, O_TRUNC
#include <stdbool.h> // bool, true, false

#define DOCC_DIR "/tmp/doc"

static int	is_closed(char *str, char desc)
{
	if ((desc == TOK_PIPE || desc == TOK_AND || desc == TOK_OR)
		&& !ft_strchr(str, '|') && !ft_strchr(str, '&'))
	{
		while (*str)
		{
			if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
				break ;
			str++;
		}
		if (*str)
			return (1);
	}
	return (0);
}

static void	doc_heredoc(char *limiter, int fd_write)
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

static void	doc_unclosed(char desc, int fd_write)
{
	char	*line;

	while (1)
	{
		write(fd_write, " ", 1);
		line = readline("> ");
		if (!line)
			break ;
		write(fd_write, line, ft_strlen(line));
		if (is_closed(line, desc))
			break ;
		if (desc == TOK_UNCLOSED_DQUOTE && ft_strchr(line, '\"'))
			break ;
		free(line);
	}
	free(line);
}

// @note newline bug when ctrl d
t_status	create_doc(t_ast *ast, bool type, char **doc)
{
	pid_t		pid;
	int			fd;
	int			status;
	char		*limiter;
	char		*suffix;

	mssignal_change_mode(MSSIG_EXEC);
	suffix = ft_itoa((long)&ast->right->token);
	limiter = ast->right->token->word;
	ast->right->token->word = ft_strjoin(DOCC_DIR, suffix);
	free(suffix);
	fd = open(ast->right->token->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1 || fd == -1)
		return (ERR_GENERALERR);
	if (pid > 0)
	{
		close(fd);
		waitpid(pid, &status, 0);
		if (type == false)
		{
			fd = open(ast->right->token->word, O_RDONLY);
			read(fd, *doc, ARG_MAX);
			close(fd);
			unlink(ast->right->token->word);
		}
		return ((t_status)WEXITSTATUS(status));
	}
	mssignal_change_mode(MSSIG_HDOC);
	if (type == true)
		doc_heredoc(limiter, fd);
	else
		doc_unclosed(ast->token->desc, fd);
	close(fd);
	exit(ERR_SUCCESS);
}