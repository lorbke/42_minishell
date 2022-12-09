/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:38:01 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/19 17:18:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_mods(t_vector *vector, t_mods *mods, char *s)
{
	int	temp;

	if (mods->precision == 1)
		temp = mods->field_prec;
	else
		temp = ft_strlen(s);
	if (mods->left == 1 || mods->space == 1 || (mods->precision == 1
			&& mods->right == 0))
		ft_vector_push_back(vector, ' ', mods->field - temp);
	return (temp);
}

void	ft_printstr(t_vector *vector, t_mods *mods, char *s)
{
	int	i;
	int	temp;

	if (s == NULL)
	{
		ft_printstr(vector, mods, "(null)");
		return ;
	}
	temp = ft_mods(vector, mods, s);
	i = 0;
	while (s[i] != 0 && i < temp)
	{
		ft_vector_push_back(vector, s[i], 1);
		i++;
	}
}
