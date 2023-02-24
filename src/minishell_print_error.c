/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:10:28 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/24 21:06:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_status
#include "lexer.h" // TOK_SUBSHELL
#include "libft.h" // ft_putstr_fd
#include <string.h> // strerror
#include <errno.h> // errno

#define STR_SYNTAXERR ": syntax error near unexpected token `"
#define STR_SYNTAXERR2 ": syntax error: unexpected end of file"
#define STR_CMDNOTFOUND ": command not found"

static void	syntax_error(int desc, char *error_loc)
{
	if (!desc && !error_loc)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(STR_SYNTAXERR2, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (desc == TOK_SUBSHELL)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(STR_SYNTAXERR, STDERR_FILENO);
		ft_putchar_fd(')', STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(STR_SYNTAXERR, STDERR_FILENO);
		ft_putstr_fd(error_loc, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
}

static void	exec_error(t_status exit_status, char *error_loc)
{
	if (exit_status == ERR_CMDNOTFOUND)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error_loc, STDERR_FILENO);
		ft_putstr_fd(STR_CMDNOTFOUND, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (exit_status >= ERR_SIGNAL && exit_status <= ERR_SIGNAL + 9)
		return ;
	else if (exit_status != ERR_SUCCESS
		&& exit_status != ERR_SYNTAX && error_loc)
	{
		if (exit_status == ERR_DIRNOTFOUND)
		{
			ms_exit_status_set(ERR_CMDNOTFOUND);
			errno = ENOENT;
		}
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error_loc, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	ms_print_error(t_status exit_status, int desc, char *error_loc)
{
	if (exit_status == ERR_SYNTAX)
		syntax_error(desc, error_loc);
	else
		exec_error(exit_status, error_loc);
}
