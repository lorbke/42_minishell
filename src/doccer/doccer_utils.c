/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doccer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:30:33 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:30:46 by lorbke           ###   ########.fr       */
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

int	is_closed(char *str)
{
	char	*pipe;
	char	*and;

	if (is_only_whitespace(str))
		return (0);
	pipe = ft_strrchr(str, '|');
	and = ft_strrchr(str, '&');
	if (pipe && is_only_whitespace(pipe + 1))
		return (0);
	if (and && is_only_whitespace(and + 1))
		return (0);
	return (1);
}
