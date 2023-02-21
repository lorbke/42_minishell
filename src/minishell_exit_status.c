/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:29:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 17:17:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // t_status
#include "parser.h" // t_ast
#include <string.h> // NULL
#include <stdio.h> // printf
#include <string.h> // strerror
#include <sys/errno.h> // errno
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <sys/wait.h> // waitpid, WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG

static t_status	*ms_exit_status_init(void)
{
	static t_status	exit_status = ERR_SUCCESS;

	return (&exit_status);
}

void	ms_exit_status_set(t_status exit_status)
{
	*ms_exit_status_init() = exit_status;
}

t_status	ms_exit_status_get(void)
{
	return (*ms_exit_status_init());
}

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
