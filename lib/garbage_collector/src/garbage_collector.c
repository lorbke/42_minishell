/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:14:34 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/21 14:34:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h" // t_garbage
#include <stdlib.h> // NULL, malloc, free

t_garbage	**garbage_init(void);

static t_garbage	*create_garbage(void *alloc, void (*func_free)(void *))
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (new == NULL)
		return (NULL);
	new->alloc = alloc;
	new->func_free = func_free;
	new->next = NULL;
	return (new);
}

static t_garbage	*append_garbage(t_garbage *main, t_garbage *append)
{
	t_garbage	*tmp;

	if (main == NULL)
		return (append);
	tmp = main;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = append;
	return (main);
}

void	gc_add_garbage(void *alloc, void (*func_free)(void *))
{
	t_garbage	*new;

	new = create_garbage(alloc, func_free);
	// if (new == NULL)
		// free all garbage, exit
	*garbage_init() = append_garbage(*garbage_init(), new);
}

void	*gc_malloc_and_add(size_t size, size_t count)
{
	void	*alloc;

	alloc = malloc(size * count);
	// if (alloc == NULL)
		// free all garbage, exit
	gc_add_garbage(alloc, free);
	return (alloc);
}

void	gc_free_all_garbage(void)
{
	t_garbage	*garbage;
	t_garbage	*temp;

	garbage = gc_get_garbage();
	while (garbage != NULL)
	{
		temp = garbage;
		garbage = garbage->next;
		temp->func_free(temp->alloc);
		free(temp);
	}
	*garbage_init() = NULL;
}