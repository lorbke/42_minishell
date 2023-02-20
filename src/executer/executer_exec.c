/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:50:15 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 16:26:41 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // cmd_table
#include "../minishell.h" // process_input, ERR_* defines
#include "../mssignal.h" // mssignal_change_mode
#include "libft.h" // ft_strlen
#include <sys/types.h> // pid_t, fork, waitpid, execve
#include <unistd.h> // STDIN_FILENO, STDOUT_FILENO, write, read
#include <stdio.h>

extern char	**environ;

static void	close_in_out_fds(int fd_in[2], int fd_out[2])
{
	if (fd_in[1] != FDLVL_STD)
		close(fd_in[0]);
	if (fd_out[1] != FDLVL_STD)
		close(fd_out[0]);
}

static pid_t	exec_subshell(t_cmd_table *cmd_table)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid != 0)
		return (pid);
	cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] = 0;
	digest_input(cmd_table->cmd[0] + 1,
		cmd_table->fd_in[0], cmd_table->fd_out[0]);
	status = exit_status_get();
	exit(status);
	return (pid);
}

static pid_t	fork_and_execve(char *path, t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
		return (pid);
	}
	mssignal_change_mode(MSSIG_NINTER);
	dup2(cmd_table->fd_in[0], STDIN_FILENO);
	dup2(cmd_table->fd_out[0], STDOUT_FILENO);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	if (fd_pipe != -1)
		close(fd_pipe);
	status = execve(path, cmd_table->cmd, environ);
	exit(status);
	return (pid);
}

// @note -1 as error sensible?
pid_t	exec_cmd(t_cmd_table *cmd_table, int fd_pipe)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (!cmd_table)
		return (-1);
	if (*cmd_table->cmd[0] == '(')
		return (exec_subshell(cmd_table));
	path = get_cmd_path(environ, cmd_table->cmd[0]);
	if (!path)
	{
		exit_status_set(ERR_CMDNOTFOUND);
		return (-1);
	}
	pid = fork_and_execve(path, cmd_table, fd_pipe);
	return (pid);
}
