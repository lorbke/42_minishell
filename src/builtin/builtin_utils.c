/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 14:21:21 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h" // ft_strcmp
#include "../builtins.h" // t_cmd_table

int	builtin_exec(t_cmd_table *cmd_table)
{
	int		i;
	int		status;
	char	*cmd;

	i = 0;
	status = RETURN_ERROR;
	cmd = cmd_table->cmd[0];
	if (ft_strcmp(cmd, "echo") == 0)
		status = echo_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		status = cd_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		status = pwd_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		status = export_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "unset") == 0)
		status = unset_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		status = env_b(cmd_table->cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		status = builtin_exit_b(cmd_table->cmd);
	return (status);
}

int	builtin_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "env") == 0)
		return (3);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (4);
	else if (ft_strcmp(cmd, "export") == 0)
		return (5);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}
