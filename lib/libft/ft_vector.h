/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:03:48 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 22:30:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_vector
{
	size_t		len;
	size_t		temp_len;
	char		*output;
}	t_vector;

void	*ft_realloc_ftprintf(void *ptr, size_t size, size_t size_src);
void	ft_vector_push_back(t_vector *vector, char c, int n);
void	ft_vector_push_back_str(t_vector *vector, char *str, int len);
void	ft_vector_init(t_vector *vector);
int		ft_vector_get_len(t_vector *vector);
char	*ft_vector_get_output(t_vector *vector);
void	ft_vector_free(t_vector *vector);

#endif
