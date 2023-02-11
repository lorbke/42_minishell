/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/11 12:20:12 by lorbke           ###   ########.fr       */
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
