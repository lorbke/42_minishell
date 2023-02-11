
#include "../executer.h" // EXEC_* defines
#include "parser.h" // t_ast
#include "executer_private.h" // exit_status_set
#include "../mssignal.h" // init_signals
#include "libft.h" // ft_strlen, ft_strncmp
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read

// @todo put heredoc str through subshell to get tokenized output
// @todo echo 1 && echo 2 print order bug
t_cmd_table	*handle_unclosed(t_ast *ast)
{
	char	*heredoc;

	heredoc = malloc(sizeof(char) * ARG_MAX);
	read(get_heredoc(heredoc_small, NULL), heredoc, ARG_MAX);
	ast->token->word = heredoc;
	ast->token->desc = TOK_WORD;
	return (create_cmd_table(ast));
}

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

	mssignal_change_mode(MSSIG_NHDOC);
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
		mssignal_change_mode(MSSIG_STD);
		exit_status_set(WEXITSTATUS(status));
		close(fd[1]);
	}
	return (fd[0]);
}
