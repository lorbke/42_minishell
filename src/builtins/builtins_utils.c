/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/16 13:46:42 by fyuzhyk          ###   ########.fr       */
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
	if (ft_strcmp(cmd, "echo") == 0)
		status = builtin_echo(cmd_table->cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		status = builtin_cd(cmd_table->cmd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		status = builtin_pwd(cmd_table->cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		status = builtin_export(cmd_table->cmd);
	else if (ft_strcmp(cmd, "unset") == 0)
		status = builtin_unset(cmd_table->cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		status = builtin_env(cmd_table->cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		status = builtin_exit(cmd_table->cmd);
	return (status);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}
