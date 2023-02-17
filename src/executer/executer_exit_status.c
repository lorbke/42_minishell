/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:20:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/17 17:18:22 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" // SHELL_NAME, t_status, ERR_* defines
#include "parser.h" // t_ast
#include <string.h> // NULL
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno

static t_status	*exit_status_init(void)
{
	static t_status	exit_status = ERR_SUCCESS;

	return (&exit_status);
}

void	exit_status_set(t_status exit_status)
{
	*exit_status_init() = exit_status;
}

t_status	exit_status_get(void)
{
	return (*exit_status_init());
}
