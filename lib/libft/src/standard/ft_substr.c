/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:31:00 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/07 16:09:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sublen;
	char	*subs;

	if (s == NULL)
		return (NULL);
	sublen = ft_strlen(&s[start]);
	if (sublen < len)
		len = sublen;
	if (ft_strlen(s) <= start)
		len = 0;
	subs = (char *)malloc(sizeof(char) * len + 1);
	if (subs == NULL)
		return (NULL);
	ft_strlcpy(subs, &s[start], len + 1);
	return (subs);
}
