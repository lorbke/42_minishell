/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:15 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:24:10 by lorbke           ###   ########.fr       */
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

/**
 * It closes the file descriptors that are not the standard ones
 * 
 * @param fd_in The input file descriptor.
 * @param fd_out The file descriptor to write to.
 */
void	exec_close_in_out_fds(int fd_in[2], int fd_out[2])
{
	if (fd_in[1] != FDLVL_STD)
		close(fd_in[0]);
	if (fd_out[1] != FDLVL_STD)
		close(fd_out[0]);
}

/**
 * It prepares the file descriptors for the execution of a command
 * 
 * @param cmd_table the command table
 * @param fd_pipe the pipe file descriptor that is used to 
 * communicate with the parent process.
 */
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

/**
 * It closes the file descriptors and sets the exit status to ERR_GENERAL
 * 
 * @param pid The pid of the child process.
 * @param cmd_table The command table that contains the command to be executed.
 * 
 * @return The pid of the child process.
 */
pid_t	exec_fork_error(pid_t pid, t_cmd_table *cmd_table)
{
	ms_exit_status_set(ERR_GENERAL);
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

/**
 * It executes a command
 * 
 * @param cmd_table A pointer to a t_cmd_table struct. This struct contains 
 * the command
 * @param fd_pipe The file descriptor of the pipe to write to.
 * 
 * @return The pid of the child process.
 */
pid_t	exec_cmd(t_cmd_table *cmd_table, int fd_pipe)
{
	int		builtin_id;

	debug_cmd_table(cmd_table);
	if (!cmd_table)
		return (RETURN_ERROR);
	else if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table, fd_pipe));
	gc_add_garbage(cmd_table->cmd, &gc_free_str_arr);
	cmd_table->cmd = expander(cmd_table->cmd);
	if (cmd_table->cmd == NULL)
		return (0);
	builtin_id = builtin_is_builtin(cmd_table->cmd[0]);
	if (builtin_id)
		return (exec_builtin(cmd_table, fd_pipe, builtin_id));
	else
		return (exec_execve(cmd_table, fd_pipe));
}
