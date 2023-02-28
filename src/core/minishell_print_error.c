/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_print_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:10:28 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 19:35:11 by lorbke           ###   ########.fr       */
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
#define STR_ERRDELIM ": "

void	ms_print_syntax_error(int desc, char *error_loc)
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
		if (ft_strchr(error_loc, '(') > ft_strchr(error_loc, ')'))
			ft_putchar_fd('(', STDERR_FILENO);
		else
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

void	ms_print_exec_error(t_status exit_status, char *error_loc)
{
	if (exit_status == ERR_CMDNOTFOUND)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(STR_ERRDELIM, STDERR_FILENO);
		ft_putstr_fd(error_loc, STDERR_FILENO);
		ft_putstr_fd(STR_CMDNOTFOUND, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (exit_status == ERR_NOPERM)
	{
		ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
		ft_putstr_fd(STR_ERRDELIM, STDERR_FILENO);
		ft_putstr_fd(error_loc, STDERR_FILENO);
		ft_putstr_fd(": permission denied\n", STDERR_FILENO);
	}
}

void	ms_print_errno(char *error_loc)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(STR_ERRDELIM, STDERR_FILENO);
	ft_putstr_fd(error_loc, STDERR_FILENO);
	ft_putstr_fd(STR_ERRDELIM, STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
