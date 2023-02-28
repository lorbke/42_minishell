/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:19:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h" // ft_strcmp
#include "../builtins.h" // t_cmd_table

/**
 * It checks if the command is a builtin, and if it is, it executes it
 * 
 * @param cmd_table This is a pointer to a t_cmd_table struct. 
 * This struct contains all the information about the command that was entered.
 * 
 * @return The status of the command.
 */
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

/**
 * It returns the number of the builtin command if it is a builtin command, 
 * and 0 if it is not
 * 
 * @param cmd The command to check.
 * 
 * @return The return value is the index of the builtin command.
 */
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
