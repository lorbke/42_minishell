/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exec_execve.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:05:55 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/25 18:34:40 by lorbke           ###   ########.fr       */
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

static pid_t	fork_and_execve(
	t_cmd_table *cmd_table, int fd_pipe, char *path, char **env)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == RETURN_ERROR)
		return (fork_error(pid, cmd_table));
	if (pid == 0)
	{
		prepare_child_for_exec(cmd_table, fd_pipe);
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
	}
	free(path);
	gc_free_str_arr(env);
	close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
	return (pid);
}

pid_t	exec_execve(t_cmd_table *cmd_table, int fd_pipe)
{
	pid_t	pid;
	char	*path;
	char	**env;

	env = create_env_list(g_sym_table);
	if (!env || ft_strchr(cmd_table->cmd[0], '/'))
		path = ft_strdup(cmd_table->cmd[0]);
	else
	{
		path = get_cmd_path(env, cmd_table->cmd[0]);
		if (path == NULL)
		{
			close_in_out_fds(cmd_table->fd_in, cmd_table->fd_out);
			gc_free_str_arr(env);
			ms_exit_status_set(ERR_CMDNOTFOUND);
			return (RETURN_ERROR);
		}
	}
	pid = fork_and_execve(cmd_table, fd_pipe, path, env);
	return (pid);
}
