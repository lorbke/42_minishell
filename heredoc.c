
#include <stdlib.h>
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <stdio.h> // FILE define (needed for readline?!)
#include <readline/readline.h> // readline
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <fcntl.h>

void	heredoc_big(char *limiter, int fd_write)
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

void	heredoc_small(char *line, int fd_write)
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

// @note newline bug when ctrl d
char	*create_heredoc(int num, void (*heredoc_type)(char *, int), char *limiter)
{
	int		fd;
	char	*dir = "/tmp/";
	char	*file;

	file = ft_strjoin(dir, ft_itoa(num));
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	(*heredoc_type)(limiter, fd);
	close(fd);
	return (file);
}

int	main(int argc, char **argv)
{
	int		fd;
	int		status;
	char	*input;
	char	*file;

	file = create_heredoc(2, heredoc_big, argv[1]);
	fd = open(file, O_RDONLY);
	input = malloc(100);
	status = read(fd, input, 100);
	printf("status: %d\n", status);
	perror("read: ");
	write(1, input, 100);
	return (0);
}
