/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:40:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 21:24:14 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_executer.h" // t_cmd_table
#include <stdlib.h> // free

/**
 * It frees the memory allocated for the command table
 * 
 * @param cmd_table_void This is the pointer to the 
 * t_cmd_table structure that you want to free.
 * 
 * @return A pointer to a t_cmd_table struct.
 */
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
