/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 13:19:24 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h" // ft_strcmp
#include "../builtins.h" // t_cmd_table

int	exec_builtin(t_cmd_table *cmd_table)
{
	int		i;
	int		status;
	char	*cmd;

	i = 0;
	status = -1;
	cmd = cmd_table->cmd[0];
	if (!ft_strcmp(cmd, "echo"))
		status = builtin_echo(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "cd"))
		status = builtin_cd(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "pwd"))
		status = builtin_pwd(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "export"))
		status = builtin_export(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "unset"))
		status = builtin_unset(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "env"))
		status = builtin_env(cmd_table->cmd);
	else if (!ft_strcmp(cmd, "exit"))
		status = builtin_exit(cmd_table->cmd);
	return (status);
}

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
