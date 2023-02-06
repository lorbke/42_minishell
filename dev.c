#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libft/libft.h"
#include "src/builtins/builtins.h"

// char	*var_expansion(char *tok_value)
// {

// }

// char	*wildcard_expansion(char *tok_value)
// {

// }

int main(int argc, char **argv, char **envp)
{
	if (ft_strncmp(builtin_arr[0].name, "echo", ft_strlen("echo")) == 0)
	{
		char *str[] = {
			"echo",
			"whaddup",
			"boi",
			NULL
		};
	}
	return(0);
}
