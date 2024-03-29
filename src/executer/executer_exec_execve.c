/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:38:40 by lorbke           ###   ########.fr       */
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

/**
 * It forks, and if the child process is created, 
 * it prepares the file descriptors for the execve call,
 * and then calls execve
 * 
 * @param cmd_table a pointer to a t_cmd_table struct, 
 * which contains all the information about the
 * command to be executed.
 * @param fd_pipe the file descriptor of the pipe to be used for the command.
 * @param path the path to the executable
 * @param env The environment variables.
 * 
 * @return The pid of the child process.
 */
static pid_t	fork_and_execve(
	t_cmd_table *cmd_table, int fd_pipe, char *path, char **env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == RETURN_ERROR)
		return (exec_fork_error(pid, cmd_table));
	else if (pid == 0)
	{
		exec_prepare_fds_for_exec(cmd_table, fd_pipe);
		status = execve(path, cmd_table->cmd, env);
		if (errno == ENOENT)
			status = ERR_CMDNOTFOUND;
		else
			status = ERR_NOPERM;
		ms_print_errno(cmd_table->cmd[0]);
		free(path);
		utils_free_split(env);
		gc_free_all_garbage();
		env_free_sym_tab(g_sym_table);
		exit(status);
	}
	free(path);
	gc_free_str_arr(env);
	exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

/**
 * It forks and execve's the command
 * 
 * @param cmd_table a pointer to a t_cmd_table struct, 
 * which contains the command to be executed, the
 * file descriptors for input and output, and the command's arguments.
 * @param fd_pipe the file descriptor of the pipe to be used for the command.
 * 
 * @return The pid of the child process.
 */
pid_t	exec_execve(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	char	*path;
	char	**env;

	env = env_create_env_list(g_sym_table);
	if (!env || ft_strchr(cmd_table->cmd[0], '/'))
	{
		path = ft_strdup(cmd_table->cmd[0]);
		if (!path)
			ft_perror_and_exit("exec_execve: ft_strup: malloc: ");
	}
	else
	{
		path = exec_get_cmd_path(env, cmd_table->cmd[0]);
		if (path == NULL)
		{
			exec_close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
			gc_free_str_arr(env);
			ms_exit_status_set(ERR_CMDNOTFOUND);
			ms_print_exec_error(ms_exit_status_get(), cmd_table->cmd[0]);
			return (RETURN_ERROR);
		}
	}
	pid = fork_and_execve(cmd_table, fd_pipe, path, env);
	return (pid);
}
