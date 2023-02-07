/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:31:19 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 11:37:02 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_private.h"

int	exec_builtin(t_cmd_table *cmd_table)
{
	int		i;
	int		status;
	char	*cmd;

	i = 0;
	status = -1;
	cmd = cmd_table->cmd[0];
	while (builtin_arr[i].name)
	{
		if (!ft_strncmp(cmd, builtin_arr[i].name, ft_strlen(cmd)))
		{
			status = builtin_arr[i].func(cmd_table->cmd);
			return (status);
		}
		i++;
	}
	return (status);
}

int	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (builtin_arr[i].name)
	{
		if (!ft_strncmp(cmd, builtin_arr[i].name, ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}
