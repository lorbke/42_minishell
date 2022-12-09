/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:24:17 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/13 11:20:50 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	number;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13 && str[i] != 0) || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	number *= sign;
	return (number);
}
