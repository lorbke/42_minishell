/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:23:41 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/19 10:04:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // ft_strchr, ft_strncmp

static void	remove_node(char *var);

int	builtin_unset(char **argv)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (argv[i] != NULL)
	{
		if (ft_isalpha(argv[i][0]))
			remove_node(argv[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			status = 1;
		}
		i++;
	}
	return (status);
}

static void	remove_first_node(t_sym_tab	*first)
{
	t_sym_tab	*temp;

	temp = first->next;
	*g_sym_table = temp;
	free(first->var);
	free(first);
}

static void	find_and_remove(char *var, t_sym_tab *temp)
{
	int			key_len;
	t_sym_tab	*prev;

	prev = *g_sym_table;
	temp = prev->next;
	while (temp != NULL)
	{
		key_len = (int)(ft_strchr(temp->var, '=') - temp->var);
		if (ft_strncmp(temp->var, var, key_len) == 0)
		{
			if (temp->next == NULL)
				prev->next = NULL;
			else
				prev->next = temp->next;
			free(temp->var);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

static void	remove_node(char *var)
{
	t_sym_tab	*temp;
	t_sym_tab	*prev;
	int			key_len;

	prev = *g_sym_table;
	temp = prev->next;
	key_len = (int)(ft_strchr(prev->var, '=') - prev->var);
	if (ft_strncmp(prev->var, var, key_len) == 0)
	{
		remove_first_node(prev);
		return ;
	}
	find_and_remove(var, temp);
}
