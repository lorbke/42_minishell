/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:11:56 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 17:29:03 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include <stdlib.h> // free

void	free_split(char **split)
{
	char **temp;

	temp = split;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(split);
}

void	free_list(t_sym_tab *head)
{
	t_sym_tab *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->name);
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
