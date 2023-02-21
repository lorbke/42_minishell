/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:30:33 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 14:14:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strrchr

int	is_only_whitespace(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
			return (0);
		str++;
	}
	return (1);
}