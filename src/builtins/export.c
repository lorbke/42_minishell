/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 14:19:58 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // ft_strchr, ft_strjoin, ft_strdup, ft_strlen, ft_strncmp
#include "../utils.h" // free_list
#include "lib/env/src/env_private.h" // add_to_back, new_sym_tab_node
#include <stdio.h> // printf

static void	export_var(t_sym_tab **sym_table, char *var);
static void	print_sorted_list(t_sym_tab *head);
static void	insertion_sort(t_sym_tab **head, t_sym_tab *node);
static void	print_var(t_sym_tab *node, char *equal);

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
	// 1 because 0 is the func itself
	i = 1;
	argc = 1;
	while (argv[argc])
		argc++;
	while (i < argc)
	{
		export_var(g_sym_table, argv[i]);
		i++;
	}
	return (0);
}

static void	export_var(t_sym_tab **sym_table, char *var)
{
	int			i;
	t_sym_tab	*temp;
	char		*search;

	i = 0;
	temp = *sym_table;
	search = malloc(sizeof(char) * ft_strlen(var));
	while (var[i] != '=' && var[i])
	{
		search[i] = var[i];
		i++;
	}
	while (temp)
	{
		if (ft_strncmp(temp->var, search, ft_strlen(search)) == 0)
		{
			temp->var = ft_strdup(var);
			return ;
		}
		temp = temp->next;
	}
	free(search);
	add_to_back(g_sym_table, new_sym_tab_node(var));
}

static void print_sorted_list(t_sym_tab *head)
{
	t_sym_tab	*next;
	t_sym_tab	*sorted;
	t_sym_tab	*current;

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
		print_var(sorted, ft_strchr(sorted->var, '='));
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

static void	print_var(t_sym_tab *node, char *equal)
{
	printf("declare -x ");
	if (equal)
	{
		// pointer subtraction here to get the length of the var name
		printf("%.*s", (int)(equal - node->var), node->var);
		printf("=");
		printf("\"%s\"", equal + 1);
		printf("\n");
	}
	else
		printf("%s\n", node->var);
}
