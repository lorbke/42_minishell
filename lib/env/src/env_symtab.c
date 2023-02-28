/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_symtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:00:37 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:15:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab, add_to_back, get_value, increase_shlvl
#include "libft.h" // free, ft_strdup, ft_strlcpy, ft_strncmp. ft_strlen

/**
 * It takes an array of strings, each of which is a variable assignment, 
 * and returns a pointer to a linked list of t_sym_tab nodes, 
 * each of which contains a variable assignment
 * 
 * @param envp The environment variables.
 * 
 * @return A pointer to a pointer to a t_sym_tab struct.
 */
t_sym_tab	**init_sym_tab(char **envp)
{
	t_sym_tab	**head;
	char		*var;

	head = malloc(sizeof(t_sym_tab));
	if (head == NULL)
		return (NULL);
	*head = NULL;
	if (envp[0] == NULL)
		return (head);
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "SHLVL=", ft_strlen("SHLVL=")) == 0)
			var = increase_shlvl(get_value(*envp));
		else
			var = ft_strdup(*envp);
		add_to_back(head, new_sym_tab_node(var));
		free(var);
		envp++;
	}
	return (head);
}

/**
 * It creates a new node for the symbol table.
 * 
 * @param var The variable name to be stored in the node.
 * 
 * @return A pointer to a t_sym_tab struct.
 */
t_sym_tab	*new_sym_tab_node(char *var)
{
	t_sym_tab	*node;

	node = malloc(sizeof(t_sym_tab));
	if (node == NULL)
		return (NULL);
	if (var == NULL)
		node->var = NULL;
	else
		node->var = ft_strdup(var);
	node->next = NULL;
	return (node);
}

/**
 * It creates a new node with the value of "?=0" and adds
 * it to the back of the linked list
 * 
 * @param head a pointer to the head of the linked list
 * 
 * @return A pointer to a new node.
 */
void	init_exit_status(t_sym_tab **head)
{
	t_sym_tab	*node;
	char		*var;

	var = malloc(sizeof(char) * ft_strlen("?=0") + 1);
	if (var == NULL)
		return ;
	ft_strlcpy(var, "?=0", ft_strlen("?=0") + 1);
	node = new_sym_tab_node(var);
	if (node && var)
		free(var);
	add_to_back(head, node);
}

/**
 * This function frees the linked list of environment variables.
 * 
 * @param head A pointer to the head of the linked list.
 * 
 * @return A pointer to a pointer to a t_sym_tab struct.
 */
void	env_free_sym_tab(t_sym_tab **head)
{
	t_sym_tab	*temp;

	while (*head != NULL)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->var);
		free(temp);
	}
	if (head == NULL)
		return ;
	free(head);
}
