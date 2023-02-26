/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:15 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 00:25:27 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "../minishell.h" // process_input, ERR_* defines
#include "../mssignal.h" // mssignal_change_mode
#include "env.h" // g_sym_table
#include "../expander.h" // expander
#include "../builtins.h" // all builtins
#include "../debugger.h" // debug functions
#include "garbage_collector.h" // gc_free_all_garbage
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read

void	exec_close_in_out_fds(int fd_in[2], int fd_out[2])
{
	if (fd_in[1] != FDLVL_STD)
		close(fd_in[0]);
	if (fd_out[1] != FDLVL_STD)
		close(fd_out[0]);
}

void	exec_prepare_fds_for_exec(t_cmd_table *cmd_table, int fd_pipe)
{
	mssignal_change_mode(MSSIG_NINTER);
	if (cmd_table->fd_in[1] != FDLVL_STD)
		dup2(cmd_table->fd_in[0], STDIN_FILENO);
	if (cmd_table->fd_out[1] != FDLVL_STD)
		dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != RETURN_ERROR)
		close(fd_pipe);
}

pid_t	exec_fork_error(pid_t pid, t_cmd_table *cmd_table)
{
	ms_exit_status_set(ERR_GENERAL);
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

pid_t	exec_cmd(t_cmd_table *cmd_table, int fd_pipe)
{
	char	*path;
	pid_t	pid;
	int		status;
	int		builtin_id;

	debug_cmd_table(cmd_table);
	if (!cmd_table)
		return (RETURN_ERROR);
	else if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table, fd_pipe));
	gc_add_garbage(cmd_table->cmd, &gc_free_str_arr);
	cmd_table->cmd = expander(cmd_table->cmd);
	builtin_id = builtin_is_builtin(cmd_table->cmd[0]);
	if (builtin_id)
		return (exec_builtin(cmd_table, fd_pipe, builtin_id));
	else
		return (exec_execve(cmd_table, fd_pipe));
}
