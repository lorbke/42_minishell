/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:25:19 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/13 11:34:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	sjoin = (char *)malloc(sizeof(char) * size);
	if (sjoin == NULL)
		return (NULL);
	ft_strlcpy(sjoin, s1, size);
	ft_strlcat(sjoin, s2, size);
	return (sjoin);
}
