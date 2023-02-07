/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 11:35:51 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "lib/env/src/env_private.h"
#include <stdio.h>

static void	free_list(t_sym_tab *head);
static void	print_sorted_list(t_sym_tab *head);
static void	insertion_sort(t_sym_tab **head, t_sym_tab *node);

// @note essentially this func has 3 modes:
// by arguments I refer to name and value
// 1. no arguments: print out the exported env variables
// 2. one argument: create a new env variable (if not already existant)
// 3. two arguments: update the value of an existing env variable or create new one

// int builtin_export(t_sym_tab **sym_table, char *name, char *value)
int builtin_export(char **argv)
{
	// t_sym_tab *temp;

	// temp = *sym_table;
	// // if no arguments are provided
	// if (name == NULL && value == NULL)
	// {
	// 	print_sorted_list(*sym_table);
	// 	return (0);
	// }
	// // if only name is provided (without value and '=')
	// if (name && value == NULL)
	// {
	// 	// first check whether the value already exists
	// 	while (temp)
	// 	{
	// 		if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
	// 		{
	// 			// if so, simply return (no changes to env variables)
	// 			return (0);
	// 		}
	// 		temp = temp->next;
	// 	}
	// 	// if not, create a new node
	// 	add_to_back(sym_table, new_sym_tab_node(name, NULL));
	// 	return (0);
	// }
	// while (temp)
	// {
	// 	// if the variable already exists, update the value
	// 	if (ft_strncmp(temp->name, name, ft_strlen(name)) == 0)
	// 	{
	// 		temp->value = value;
	// 		return (0);
	// 	}
	// 	temp = temp->next;
	// }
	// // if not, create a new node
	// add_to_back(sym_table, new_sym_tab_node(name, value));
	return (0);
}

static void print_sorted_list(t_sym_tab *head)
{
	t_sym_tab *next;
	t_sym_tab *sorted;
	t_sym_tab *current;

	sorted = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		insertion_sort(&sorted, current);
		current = next;
	}
	while (sorted)
	{
		printf("declare -x ");
		printf("%s", sorted->name);
			if (sorted->value != NULL)
				printf("=\"%s\"", sorted->value);
			printf("\n");
		sorted = sorted->next;
	}
	free_list(sorted);
}

static void insertion_sort(t_sym_tab **head, t_sym_tab *node)
{
	int			i;
	t_sym_tab	*temp;
	t_sym_tab	*current;

	i = 0;
	temp = copy_node(node);
	if (*head == NULL || (*head)->name[i] >= temp->name[i])
	{
		if (*head == NULL)
			temp->next = NULL;
		else
			temp->next = *head;
		*head = temp;
	}
	else
	{
		current = *head;
		while((*head)->name[i] == temp->name[i])
			i++;
		while (current->next != NULL && current->next->name[i] < temp->name[i])
			current = current->next;
		temp->next = current->next;
		current->next = temp;
	}
}

static void	free_list(t_sym_tab *head)
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
