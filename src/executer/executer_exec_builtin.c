/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:05:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 00:16:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "../minishell.h" // process_input, ERR_* defines
#include "../mssignal.h" // mssignal_change_mode
#include "env.h" // g_sym_table
#include "../utils.h"
#include "../expander.h" // expander
#include "../builtins.h" // all builtins
#include "garbage_collector.h" // gc_free_all_garbage
#include "libft.h" // ft_strlen
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <stdlib.h> // free
#include <sys/errno.h> // errno

static pid_t	case_fork(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == RETURN_ERROR)
		return (exec_fork_error(pid, cmd_table));
	if (pid == 0)
	{
		exec_prepare_fds_for_exec(cmd_table, fd_pipe);
		if (fd_pipe != RETURN_ERROR)
			close(fd_pipe);
		status = builtin_exec(cmd_table);
		gc_free_all_garbage();
		env_free_sym_tab(g_sym_table);
		exit(status);
		return (pid);
	}
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

static pid_t	case_no_fork(t_cmd_table *cmd_table)
{
	int		fd_temp;
	int		status;

	fd_temp = dup(STDOUT_FILENO);
	dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	status = builtin_exec(cmd_table);
	ms_exit_status_set(status);
	dup2(fd_temp, STDOUT_FILENO);
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	close(fd_temp);
	return (RETURN_ERROR);
}

pid_t	exec_builtin(t_cmd_table *cmd_table, int fd_pipe)
{
	if (!isatty(STDOUT_FILENO) && ft_strcmp(cmd_table->cmd[0], "echo") == 0)
		return (case_fork(cmd_table, fd_pipe));
	if (cmd_table->fd_in[1] != FDLVL_PIPE
		&& cmd_table->fd_out[1] != FDLVL_PIPE)
		return (case_no_fork(cmd_table));
	else
		return (case_fork(cmd_table, fd_pipe));
}
