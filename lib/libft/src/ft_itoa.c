/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:23:20 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/13 11:35:08 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		sign;

	len = ft_intlen(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (num == NULL)
		return (NULL);
	sign = 1;
	if (n < 0)
		sign = -1;
	else
		n *= -1;
	if (n == 0)
		num[0] = '0';
	num[len] = 0;
	while (n != 0)
	{
		num[len - 1] = (n % 10) * -1 + '0';
		n /= 10;
		len--;
	}
	if (sign < 0)
		num[len - 1] = '-';
	return (num);
}
