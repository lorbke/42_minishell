/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/08 07:54:29 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "../free.h"
#include "lib/env/src/env_private.h"
#include <stdio.h>

static void	export_var(char *arg);
static void	print_sorted_list(t_sym_tab *head);
static void	insertion_sort(t_sym_tab **head, t_sym_tab *node);
static void	create_entry(t_sym_tab **sym_table, char *var);

extern t_sym_tab **g_sym_table;

int builtin_export(char **argv)
{
	int		i;
	int		argc;
	char	**var;

	// if no arguments are provided
	if (argv[1] == NULL)
	{
		print_sorted_list(*g_sym_table);
		return (0);
	}
	i = 0;
	argc = 0;
	while (argv[argc])
		argc++;
	while (i < argc)
	{
		export_var(argv[i]);
		i++;
	}
	return (0);
}

static void	create_entry(t_sym_tab **sym_table, char *var)
{
	t_sym_tab *temp;

	temp = *sym_table;
	while (temp)
	{
		// if the variable already exists, update the value
		if (ft_strncmp(temp->var, var, ft_strlen(var)) == 0)
		{
			temp->var = ft_strdup(var);
			return ;
		}
		temp = temp->next;
	}
	// if not, create new entry (name + value)
	add_to_back(g_sym_table, new_sym_tab_node(var));
}

static void	export_var(char *arg)
{
	create_entry(g_sym_table, arg);
}

static void print_sorted_list(t_sym_tab *head)
{
	t_sym_tab	*next;
	t_sym_tab	*sorted;
	t_sym_tab	*current;
	char		*equal;

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
		equal = ft_strchr(sorted->var, '=');
		if(equal)
		{
			// wtf is this
			printf("%.*s", (int)(equal - sorted->var), sorted->var);
			printf("\"%s\"", equal + 1);
		}
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
	if (*head == NULL || (*head)->var[i] >= temp->var[i])
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
		while((*head)->var[i] == temp->var[i])
			i++;
		while (current->next != NULL && current->next->var[i] < temp->var[i])
			current = current->next;
		temp->next = current->next;
		current->next = temp;
	}
}
