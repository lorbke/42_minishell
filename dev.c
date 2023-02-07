#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/env/env.h"
#include "src/builtins.h"
#include "lib/libft/libft.h"

// char	*var_expansion(char *tok_value)
// {

// }

// char	*wildcard_expansion(char *tok_value)
// {

// }

extern t_sym_tab **g_sym_table;

int main(int argc, char **argv, char **envp)
{
	builtin_export(argv);

	return(0);
}
