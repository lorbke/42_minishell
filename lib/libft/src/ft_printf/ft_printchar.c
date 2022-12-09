/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:12:34 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/18 21:05:28 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_mods(t_vector *vector, t_mods *mods)
{
	int	temp;

	if (mods->precision == 1)
		temp = mods->field_prec;
	else
		temp = 1;
	if (mods->left == 1 || mods->space == 1 || (mods->precision == 1
			&& mods->right == 0))
		ft_vector_push_back(vector, ' ', mods->field - temp);
	return (temp);
}

void	ft_printchar(t_vector *vector, t_mods *mods, char c)
{
	ft_mods(vector, mods);
	ft_vector_push_back(vector, c, 1);
}
