/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:57:55 by lorbke            #+#    #+#             */
/*   Updated: 2022/10/14 21:04:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

char	*ft_vector_get_output(t_vector *vector)
{
	return (vector->output);
}

int	ft_vector_get_len(t_vector *vector)
{
	return (vector->temp_len);
}

void	ft_vector_free(t_vector *vector)
{
	free(vector->output);
}
