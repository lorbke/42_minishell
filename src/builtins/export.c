/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 18:02:04 by fyuzhyk          ###   ########.fr       */
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
static void	create_entry(t_sym_tab **sym_table, char **args, int i);

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

static void	create_entry(t_sym_tab **sym_table, char **args, int i)
{
	t_sym_tab *temp;

	temp = *sym_table;
	while (temp)
	{
		// if the variable already exists, update the value
		if (ft_strncmp(temp->name, args[0], ft_strlen(args[0])) == 0)
		{
			if (args[1] != NULL)
				temp->value = args[1];
			free_split(args);
			return ;
		}
		temp = temp->next;
	}
	// if not, create new entry (name + value)
	if (args[1] == NULL && i == 0)
		add_to_back(g_sym_table, new_sym_tab_node(args[0], NULL));
	else if (args[1] && i >= 1)
		add_to_back(g_sym_table, new_sym_tab_node(args[0], args[1]));
	else
		add_to_back(g_sym_table, new_sym_tab_node(args[0], ""));
}

static void	export_var(char *arg)
{
	int		i;
	char	**var;

	i = 0;
	var = ft_split(arg, '=');
	char *equal = ft_strchr(arg, '=');
	if (equal)
		i = 1;
	create_entry(g_sym_table, var, i);
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
