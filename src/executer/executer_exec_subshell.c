/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_subshell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 23:54:19 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/26 00:15:32 by lorbke           ###   ########.fr       */
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

static int	check_subshell_syntax(t_cmd_table *cmd_table)
{
	if (cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] != ')'
		|| ft_strlen(cmd_table->cmd[0]) < 3)
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_error(ms_exit_status_get(), 0, cmd_table->cmd[0]);
		return (RETURN_ERROR);
	}
	return (1);
}

static void	case_child(t_cmd_table *cmd_table, int fd_pipe)
{
	int		status;

	exec_prepare_fds_for_exec(cmd_table, fd_pipe);
	cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] = 0;
	ms_digest_input(cmd_table->cmd[0] + 1);
	status = ms_exit_status_get();
	gc_free_all_garbage();
	env_free_sym_tab(g_sym_table);
	exit(status);
}

pid_t	exec_subshell(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;

	if (check_subshell_syntax(cmd_table) == RETURN_ERROR)
		return (RETURN_ERROR);
	pid = fork();
	if (pid == RETURN_ERROR)
		return (exec_fork_error(pid, cmd_table));
	else if (pid == 0)
		case_child(cmd_table, fd_pipe);
	else
		exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}
