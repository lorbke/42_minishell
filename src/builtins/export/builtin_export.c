/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:13:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/26 20:32:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table, add_to_back, new_sym_tab_node
#include "libft.h" // ft_strchr, ft_strjoin, ft_strdup, ft_strlen, ft_strncmp
#include "../../utils.h" // free_list
#include "export_private.h" // init_var_name, init_var_value, check_if_var_exists
#include "../../../lib/env/src/env_private.h" // copy_node
#include <stdio.h> // printf

static int	export_var(char *var);
static void	print_sorted_list(t_sym_tab *head);
static void	insertion_sort(t_sym_tab **head, t_sym_tab *node);
static void	print_var(t_sym_tab *node, char *equal);

int export_b(char **argv)
{
	int		i;
	int		argc;
	int		status;
	char	**var;

	status = 0;
	if (argv[1] == NULL)
	{
		print_sorted_list(*g_sym_table);
		return (0);
	}
	i = 1;
	argc = 1;
	while (argv[argc] != NULL)
		argc++;
	while (i < argc)
	{
		if (export_var(argv[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

static int	export_var(char *var)
{
	char	*var_name;
	char	*var_value;
	char	*variable;

	var_name = init_var_name(var);
	if (var_name == NULL)
		return (1);
	var_value = init_var_value(var, var_name);
	if (update_if_exists(var_name, var_value))
		return (0);
	variable = malloc(sizeof(char) * ft_strlen(var) + 1);
	if (variable == NULL)
		return (1);
	ft_strlcpy(variable, var, ft_strlen(var) + 1);
	if (var_value != NULL)
	{
		free(variable);
		variable = ft_strjoin(var_name, var_value);
	}
	add_to_back(g_sym_table, new_sym_tab_node(variable));
	free(var_name);
	free(var_value);
	free(variable);
	return (0);
}

static void print_sorted_list(t_sym_tab *head)
{
	t_sym_tab	*next;
	t_sym_tab	*current;
	t_sym_tab	*sorted;

	sorted = NULL;
	current = head;
	while (current != NULL)
	{
		next = current->next;
		insertion_sort(&sorted, current);
		current = next;
	}
	while (sorted != NULL)
	{
		current = sorted;
		print_var(sorted, ft_strchr(sorted->var, '='));
		sorted = sorted->next;
		free(current->var);
		free(current);
	}
}

static void insertion_sort(t_sym_tab **head, t_sym_tab *node)
{
	int			i;
	t_sym_tab	*temp;
	t_sym_tab	*current;

	i = 0;
	temp = copy_node(node);
	if (temp == NULL)
		return ;
	if (*head == NULL || ft_strcmp((*head)->var, temp->var) >= 0)
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
		while (current->next != NULL && ft_strcmp(current->next->var, temp->var) < 0)
			current = current->next;
		temp->next = current->next;
		current->next = temp;
	}
}

static void	print_var(t_sym_tab *node, char *equal)
{
	if (ft_strncmp(node->var, "?=", 2) == 0)
		return ;
	printf("declare -x ");
	if (equal)
	{
		printf("%.*s", (int)(equal - node->var), node->var);
		printf("=");
		printf("\"%s\"", equal + 1);
		printf("\n");
	}
	else
		printf("%s\n", node->var);
}
