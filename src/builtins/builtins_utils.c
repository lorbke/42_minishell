/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/08 08:48:52 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "builtins_private.h"

int	exec_builtin(t_cmd_table *cmd_table)
{
	int		i;
	int		status;
	char	*cmd;

	i = 0;
	status = -1;
	cmd = cmd_table->cmd[0];
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		status = builtin_echo(cmd_table->cmd);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		status = builtin_cd(cmd_table->cmd);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		status = builtin_pwd(cmd_table->cmd);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		status = builtin_export(cmd_table->cmd);
	// else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
	// 	status = builtin_unset(cmd_table->cmd);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		status = builtin_env(cmd_table->cmd);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		status = builtin_exit(cmd_table->cmd);
	return (status);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (1);
	else if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (1);
	else if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (1);
	else if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (1);
	else if (!ft_strncmp(cmd, "env", ft_strlen("env")))
		return (1);
	else if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (1);
	return (0);
}
