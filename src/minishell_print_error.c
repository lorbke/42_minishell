/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:10:28 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/23 01:36:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_status
#include "lexer.h" // TOK_SUBSHELL
#include <unistd.h> // STD*_* defines, dup
#include <stdio.h> // printf
#include <string.h> // strerror
#include <errno.h> // errno

#define STR_SYNTAXERR ": syntax error near unexpected token `"

static void	syntax_error(int desc, char *error_loc)
{
	if (!desc && !error_loc)
		printf("%s: syntax error: unexpected end of file\n", SHELL_NAME);
	else if (desc == TOK_SUBSHELL)
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, "(");
	else
		printf("%s%s%s'\n",
			SHELL_NAME, STR_SYNTAXERR, error_loc);
}

static void	exec_error(t_status exit_status, char *error_loc)
{
	if (exit_status == ERR_CMDNOTFOUND)
		printf("%s: %s: command not found\n", SHELL_NAME, error_loc);
	else if (exit_status >= ERR_SIGNAL && exit_status <= ERR_SIGNAL + 9)
		return ;
	else if (exit_status != ERR_SUCCESS
		&& exit_status != ERR_SYNTAX && error_loc)
		printf("%s: %s: %s\n", SHELL_NAME, error_loc, strerror(errno));
}

void	ms_print_error(t_status exit_status, int desc, char *error_loc)
{
	int	temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (exit_status == ERR_SYNTAX)
		syntax_error(desc, error_loc);
	else
		exec_error(exit_status, error_loc);
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
}
