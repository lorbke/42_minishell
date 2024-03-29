/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:15:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 20:28:07 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <sys/types.h> // size_t

/* This set of functions will keep track of memory allocations which can
be added as pointers. The allocations can then later be freed. */

typedef struct s_garbage
{
	void				*alloc;
	void				(*func_free)(void *);
	struct s_garbage	*next;
}	t_garbage;

t_garbage	*gc_get_garbage(void);
void		gc_add_garbage(void *alloc, void (*func_free)(void *));
void		*gc_malloc_and_add(size_t size, size_t count);
void		gc_free_all_garbage(void);

// free functions
void		gc_free_str_arr(void *str_arr_void);

#endif
