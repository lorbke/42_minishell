/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:15 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/23 22:05:19 by lorbke           ###   ########.fr       */
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

#include <stdio.h>
static void	close_in_out_fds(int fd_in[2], int fd_out[2])
{
	if (fd_in[1] != FDLVL_STD)
		close(fd_in[0]);
	if (fd_out[1] != FDLVL_STD)
		close(fd_out[0]);
}

static pid_t	exec_subshell(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	if (cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] != ')')
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_error(ms_exit_status_get(), 0, cmd_table->cmd[0]);
		return (-1);
	}
	pid = fork();
	if (pid > 0)
	{
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] = 0;
	ms_digest_input(cmd_table->cmd[0] + 1,
		cmd_table->fd_in[0], cmd_table->fd_out[0]);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != -1)
		close(fd_pipe);
	status = ms_exit_status_get();
	gc_free_all_garbage();
	exit(status);
	return (pid);
}

static pid_t
	fork_and_execve(char *path, char **env, t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		free(path);
		free_split(env);
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	mssignal_change_mode(MSSIG_NINTER);
	dup2(cmd_table->fd_in[0], STDIN_FILENO);
	dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != -1)
		close(fd_pipe);
	if (!path)
		status = execve(cmd_table->cmd[0], cmd_table->cmd, env);
	else
		status = execve(path, cmd_table->cmd, env);
	if (errno == ENOENT)
		status = ERR_DIRNOTFOUND;
	else
		status = ERR_NOPERM;
	free(path);
	free_split(env);
	gc_free_all_garbage();
	exit(status);
	return (pid);
}

// @todo pid error handling
static pid_t	exec_builtin(t_cmd_table *cmd_table)
{
	pid_t	pid;
	int		status;
	int		fd_temp;

	if (cmd_table->fd_in[1] != FDLVL_PIPE
		&& cmd_table->fd_out[1] != FDLVL_PIPE)
	{
		fd_temp = dup(STDOUT_FILENO);
		dup2(cmd_table->fd_out[0], STDOUT_FILENO);
		status = builtin_exec(cmd_table);
		dup2(fd_temp, STDOUT_FILENO);
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		close(fd_temp);
		ms_exit_status_set(status);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
		return (pid);
	if (pid > 0)
	{
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	mssignal_change_mode(MSSIG_NINTER);
	status = builtin_exec(cmd_table);
	gc_free_all_garbage();
	exit(status);
	return (pid);
}

pid_t	exec_cmd(t_cmd_table *cmd_table, int fd_pipe)
{
	char	*path;
	char	**env;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table, fd_pipe));
	env = create_env_list(g_sym_table);
	cmd_table->cmd = expander(cmd_table->cmd);
	if (builtin_is_builtin(cmd_table->cmd[0]))
	{
		// @note needs to be protected
		if (env != NULL)
			gc_free_str_arr(env);
		return (exec_builtin(cmd_table));
	}
	path = NULL;
	// @note also needs to be protected if env == NULL
	if (env != NULL && !ft_strchr(cmd_table->cmd[0], '/'))
	{
		path = get_cmd_path(env, cmd_table->cmd[0]);
		if (!path)
		{
			if (env != NULL)
				gc_free_str_arr(env);
			close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
			ms_exit_status_set(ERR_CMDNOTFOUND);
			return (-1);
		}
	}
	// gc_add_garbage(cmd_table->cmd, &gc_free_str_arr);
	return (fork_and_execve(path, env, cmd_table, fd_pipe));
}
