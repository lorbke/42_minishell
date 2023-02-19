
#include <stdlib.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h>

#define DOCC_DIR "/tmp/heredoc"
# define ERR_SUCCESS 0
# define ERR_GENERALERR 1 
# define ERR_SYNTAXERR 2
# define ERR_CMDNOTFOUND 127
# define ERR_SIGNAL 128

typedef unsigned char	t_status;

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		sign;

	len = ft_intlen(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (num == NULL)
		return (NULL);
	sign = 1;
	if (n < 0)
		sign = -1;
	else
		n *= -1;
	if (n == 0)
		num[0] = '0';
	num[len] = 0;
	while (n != 0)
	{
		num[len - 1] = (n % 10) * -1 + '0';
		n /= 10;
		len--;
	}
	if (sign < 0)
		num[len - 1] = '-';
	return (num);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = strlen(s1) + strlen(s2) + 1;
	sjoin = (char *)malloc(sizeof(char) * size);
	if (sjoin == NULL)
		return (NULL);
	strlcpy(sjoin, s1, size);
	strlcat(sjoin, s2, size);
	return (sjoin);
}

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

// @note newline bug when ctrl d
t_status	create_doc(t_ast *ast, void (*doc_type)(char *, int))
{
	pid_t		pid;
	int			fd;
	int			status;
	char		*limiter;
	char		*suffix;

	// mssignal_change_mode(MSSIG_EXEC);
	suffix = ft_itoa((int)&ast->token->word);
	limiter = ast->token->word;
	ast->token->word = ft_strjoin(DOCC_DIR, suffix);
	free(suffix);
	fd = open(ast->token->word, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1 || fd == -1)
		return (ERR_GENERALERR);
	if (pid > 0)
	{
		close(fd);
		waitpid(pid, &status, 0);
		return ((t_status)WEXITSTATUS(status));
	}
	// mssignal_change_mode(MSSIG_HDOC);
	(*doc_type)(limiter, fd);
	close(fd);
	exit(ERR_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		status;
	char	*input;
	char	*file;

	file = create_doc(2, doc_heredoc, argv[1]);
	fd = open(file, O_RDONLY);
	input = malloc(100);
	status = read(fd, input, 100);
	printf("status: %d\n", status);
	perror("read: ");
	write(1, input, 100);
	return (0);
}
