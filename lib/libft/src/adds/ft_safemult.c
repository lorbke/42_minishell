/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safemult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 22:14:44 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/06 22:24:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function will multiply two given integers only 
when there is no overflow or underflow occuring. */
int	ft_safemult(int a, int b)
{
	if (a == 0 || b == 0)
		return (0);
	if ((a < 0 || b < 0) && INT_MIN / a > b)
	{
		errno = ERANGE;
		return (INT_MIN);
	}
	if (INT_MAX / a < b)
	{
		errno = ERANGE;
		return (INT_MAX);
	}
	return (a * b);
}
