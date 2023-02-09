/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 15:44:12 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executer.h" // EXEC_* defines
#include "../minishell.h" // SHELL_NAME
#include "parser.h" // t_ast
#include <string.h> // NULL
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno

static char	*exit_status_init(void)
{
	static char	exit_status = EXEC_SUCCESS;

	return (&exit_status);
}

void	exit_status_set(char exit_status)
{
	*exit_status_init() = exit_status;
}

char	exit_status_get(void)
{
	return (*exit_status_init());
}

void	print_error(char exit_status, char *error_loc)
{
	if (exit_status == EXEC_CMDNOTFOUND)
		printf("%s: %s: command not found\n", SHELL_NAME, error_loc);
	else if (exit_status != EXEC_SUCCESS)
		printf("%s: %s: %s\n", SHELL_NAME, error_loc, strerror(errno));
}
