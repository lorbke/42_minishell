/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:24:17 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/23 22:33:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*get_start(const char *str, int *sign)
{
	while ((*str >= 9 && *str <= 13 && *str != 0) || *str == ' ')
		str++;
	*sign = 1;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

/* This version of the ft_atoi function is able to handle doubles.*/
double	ft_atof(const char *str)
{
	int		sign;
	int		afterdot;
	double	scale;
	double	number;

	str = get_start(str, &sign);
	afterdot = 0;
	scale = 1;
	number = 0;
	while ((*str >= '0' && *str <= '9' && *str != 0) || *str == '.')
	{
		if (afterdot)
		{
			scale = scale / 10.0;
			number += (*str - '0') * scale;
		}
		else if (*str == '.')
			afterdot = 1;
		else
			number = number * 10.0 + (*str - '0');
		str++;
	}
	number *= (double) sign;
	return (number);
}
