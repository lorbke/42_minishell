/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_symtab_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:03:21 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:35:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, NULL, ft_strdup
#include "env.h" // t_sym_tab

/**
 * It gets the length of a linked list
 * 
 * @param head the head of the linked list
 * 
 * @return The length of the linked list.
 */
int	get_list_len(t_sym_tab **head)
{
	t_sym_tab	*temp;
	int			len;

	len = 0;
	temp = *head;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

/**
 * It returns the last node of a linked list
 * 
 * @param lst The list to add the new node to.
 * 
 * @return The last node in the list.
 */
t_sym_tab	*get_last_node(t_sym_tab *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/**
 * It takes a string of the form "SHLVL=<number>" and returns a 
 * string of the form "SHLVL=<number + 1>"
 * 
 * @param shlvl The current value of SHLVL.
 * 
 * @return A string that is the value of the SHLVL environment variable.
 */
char	*increase_shlvl(char *shlvl)
{
	int		lvl;
	char	*lvl_str;
	char	*new_shlvl;

	if (shlvl == NULL)
		lvl = 1;
	else
		lvl = ft_atoi(shlvl) + 1;
	lvl_str = ft_itoa(lvl);
	new_shlvl = ft_strjoin("SHLVL=", lvl_str);
	free(lvl_str);
	free(shlvl);
	return (new_shlvl);
}

void	env_add_to_back(t_sym_tab **lst, t_sym_tab *new_node)
{
	t_sym_tab	*temp;

	if (*lst != NULL)
	{
		temp = get_last_node(*lst);
		temp->next = new_node;
	}
	else
		*lst = new_node;
}

t_sym_tab	*env_copy_node(t_sym_tab *node)
{
	t_sym_tab	*new_node;

	new_node = malloc(sizeof(t_sym_tab));
	if (new_node == NULL)
		return (NULL);
	new_node->var = ft_strdup(node->var);
	new_node->next = NULL;
	return (new_node);
}
