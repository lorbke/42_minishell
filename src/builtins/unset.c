/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:23:41 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 17:48:17 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // ft_strchr, ft_strncmp

static void	remove_node(char *var);

int	builtin_unset(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		remove_node(argv[i]);
		i++;
	}
	return (0);
}

static void	remove_first_node(t_sym_tab	*first)
{
	t_sym_tab	*temp;

	temp = first->next;
	*g_sym_table = temp;
	free(first->var);
	free(first);
}

static void	remove_node(char *var)
{
	t_sym_tab	*temp;
	t_sym_tab	*prev;
	int			key_len;

	prev = *g_sym_table;
	temp = (*g_sym_table)->next;
	key_len = (int)(ft_strchr(prev->var, '=') - prev->var);
	if (ft_strncmp(prev->var, var, key_len) == 0)
	{
		remove_first_node(prev);
		return ;
	}
	while (temp != NULL)
	{
		key_len = (int)(ft_strchr(temp->var, '=') - temp->var);
		if (ft_strncmp(temp->var, var, key_len) == 0)
		{
			prev->next = temp->next;
			free(temp->var);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}
