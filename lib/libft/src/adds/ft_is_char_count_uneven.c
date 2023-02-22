/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_char_uneven.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:24:18 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/22 17:26:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_char_count_uneven(char *str, char c)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count % 2);
}
