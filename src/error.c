/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:33:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/08 18:40:46 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // SHELL_NAME
#include "executer.h" // EXEC_* defines
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno

void	print_exec_error(char exit_status, char *error_loc)
{
	if (exit_status == EXEC_CMDNOTFOUND)
		printf("%s: %s: command not found\n", SHELL_NAME, error_loc);
	else if (exit_status != EXEC_SUCCESS)
		printf("%s: %s: %s\n", SHELL_NAME, error_loc, strerror(errno));
}
