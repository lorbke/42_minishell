/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_obj.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:18:46 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 21:27:12 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h" // t_garbage
#include <stdlib.h> // NULL

t_garbage	**garbage_init(void)
{
	static t_garbage	*garbage = NULL;

	return (&garbage);
}

t_garbage	*gc_get_garbage(void)
{
	return (*garbage_init());
}
