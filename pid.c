#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int	main(void)
{
	int	status;

	status = 0;
	waitpid(0, &status, 0);
	if (WIFSIGNALED(status))
	{
		printf("status: %d\n", WEXITSTATUS(status));
	}
	return (0);
}
