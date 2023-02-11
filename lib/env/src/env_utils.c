/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:20:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/11 14:38:56 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env_private.h"

static int	check_value(t_sym_tab *node);

//@note you are mallocing the env list here
// possible that this will cause leaks when called with execve?
// or does it free this automatically?
char **create_env_list(t_sym_tab **head)
{
	int			i;
	int			len;
	t_sym_tab	*temp;
	char		**env_list;

	//@note check if it is possible to do it this way, without malloc
	len = get_list_len(head);
	env_list = malloc(sizeof(char *) * (len + 1));
	if (env_list == NULL) {
		// @note need to handle this error properly
	}
	temp = *head;
	i = 0;
	while (temp) {
		if (!check_value(temp))
			temp = temp->next;
		else
		{
			env_list[i] = temp->var;
			temp = temp->next;
			i++;
		}
	}
	return (env_list);
}

static int	check_value(t_sym_tab *node)
{
	if (!node)
		return (0);
	if (ft_strchr(node->var, '='))
		return (1);
	else
		return (0);
}
