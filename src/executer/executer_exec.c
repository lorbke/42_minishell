/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:15 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/25 17:12:01 by lorbke           ###   ########.fr       */
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

void	close_in_out_fds(int fd_in[2], int fd_out[2])
{
	if (fd_in[1] != FDLVL_STD)
		close(fd_in[0]);
	if (fd_out[1] != FDLVL_STD)
		close(fd_out[0]);
}

void	prepare_child_for_exec(t_cmd_table *cmd_table, int fd_pipe)
{
	mssignal_change_mode(MSSIG_NINTER);
	dup2(cmd_table->fd_in[0], STDIN_FILENO);
	dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != RETURN_ERROR)
		close(fd_pipe);
}

pid_t	fork_error(pid_t pid, t_cmd_table *cmd_table)
{
	ms_exit_status_set(ERR_GENERAL);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

static pid_t	exec_subshell(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	if (cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] != ')'
		|| ft_strlen(cmd_table->cmd[0]) < 3)
	{
		ms_exit_status_set(ERR_SYNTAX);
		ms_print_error(ms_exit_status_get(), 0, cmd_table->cmd[0]);
		return (RETURN_ERROR);
	}
	pid = fork();
	if (pid == RETURN_ERROR)
		return (fork_error(pid, cmd_table));
	if (pid > 0)
	{
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] = 0;
	ms_digest_input(cmd_table->cmd[0] + 1,
		cmd_table->fd_in[0], cmd_table->fd_out[0]);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != RETURN_ERROR)
		close(fd_pipe);
	status = ms_exit_status_get();
	gc_free_all_garbage();
	env_free_sym_tab(g_sym_table);
	exit(status);
	return (pid);
}

static pid_t
	fork_and_execve(char *path, char **env, t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == RETURN_ERROR)
		return (fork_error(pid, cmd_table));
	if (pid > 0)
	{
		free(path);
		free_split(env);
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	prepare_child_for_exec(cmd_table, fd_pipe);
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
	env_free_sym_tab(g_sym_table);
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
		return (RETURN_ERROR);
	if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table, fd_pipe));
	env = create_env_list(g_sym_table);
	gc_add_garbage(cmd_table->cmd, gc_free_str_arr);
	cmd_table->cmd = expander(cmd_table->cmd);
	if (builtin_is_builtin(cmd_table->cmd[0]))
	{
		if (env != NULL)
			gc_free_str_arr(env);
		return (exec_builtin(cmd_table, fd_pipe));
	}
	path = NULL;
	if (env != NULL && !ft_strchr(cmd_table->cmd[0], '/'))
	{
		path = get_cmd_path(env, cmd_table->cmd[0]);
		if (!path)
		{
			if (env != NULL)
				gc_free_str_arr(env);
			close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
			ms_exit_status_set(ERR_CMDNOTFOUND);
			return (RETURN_ERROR);
		}
	}
	return (fork_and_execve(path, env, cmd_table, fd_pipe));
}
