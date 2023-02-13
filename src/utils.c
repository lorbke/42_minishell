/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 14:18:15 by fyuzhyk          ###   ########.fr       */
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
		free(temp->var);
		free(temp);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && s2[i] != 0 && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
