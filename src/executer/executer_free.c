/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:40:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/27 14:35:45 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table
#include <stdlib.h> // free

void	executer_free_cmd_table(void *cmd_table_void)
{
	t_cmd_table	*cmd_table;
	int			i;

	cmd_table = (t_cmd_table *)cmd_table_void;
	if (cmd_table->cmd == NULL)
	{
		free(cmd_table);
		return ;
	}
	i = 0;
	while (cmd_table->cmd[i])
	{
		free(cmd_table->cmd[i]);
		i++;
	}
	free(cmd_table->cmd);
	free(cmd_table);
}
