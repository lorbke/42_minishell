/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:29:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 20:33:02 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_status
#include "parser.h" // t_ast
#include "../lib/env/env.h" // g_sym_table
#include "libft.h"
#include <string.h> // NULL
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <sys/wait.h> // waitpid, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG

void	ms_exit_status_set(t_status exit_status)
{
	t_sym_tab	*tmp;
	char		*exit_status_str;

	tmp = *g_sym_table;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, "?=", 2) == 0)
		{
			free(tmp->var);
			exit_status_str = ft_itoa(exit_status);
			tmp->var = ft_strjoin("?=", exit_status_str);
			free(exit_status_str);
			return ;
		}
		tmp = tmp->next;
	}
}

t_status	ms_exit_status_get(void)
{
	t_sym_tab	*tmp;
	t_status	exit_status;

	tmp = *g_sym_table;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, "?=", 2) == 0)
		{
			exit_status = ft_atoi(tmp->var + 2);
			return (exit_status);
		}
		tmp = tmp->next;
	}
}

// @todo parent processs builtin exit status is overwritten
void	ms_wait_pid_and_set_exit(pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_exit_status_set(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		ms_exit_status_set(ERR_SIGNAL + WTERMSIG(status));
		if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit: 3", 7);
		write(STDOUT_FILENO, "\n", 1);
	}
}
