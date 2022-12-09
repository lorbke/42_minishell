/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safeint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 21:53:32 by lorbke            #+#    #+#             */
/*   Updated: 2022/11/06 22:10:18 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* This function will add two given integers only 
when there is no overflow or underflow occuring. */
int	ft_safeadd(int a, int b)
{
	if (a > 0 && b > INT_MAX - a)
	{
		errno = ERANGE;
		return (INT_MAX);
	}
	else if (a < 0 && b < INT_MIN - a)
	{
		errno = ERANGE;
		return (INT_MIN);
	}
	return (a + b);
}
