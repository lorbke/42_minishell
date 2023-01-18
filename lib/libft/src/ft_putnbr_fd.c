/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:44:29 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/12 17:48:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	temp;

	temp = n;
	if (temp < 0 && n / 10 == 0)
		write (fd, "-", 1);
	if (temp >= 0)
		temp *= -1;
	temp = temp % 10 * -1 + '0';
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	write(fd, &temp, 1);
}
