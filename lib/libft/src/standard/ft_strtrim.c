/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 12:50:11 by lorbke            #+#    #+#             */
/*   Updated: 2022/04/08 16:32:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkfront(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != 0 && set[j] != 0)
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_checkend(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(s1);
	if (len <= 0)
		return (0);
	i = len - 1;
	j = 0;
	while (s1[i] != 0 && set[j] != 0)
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (len - i - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*scpy;
	int		cpylen;
	int		front;
	int		end;

	if (s1 == NULL)
		return (NULL);
	front = ft_checkfront(s1, set);
	end = ft_checkend(&s1[front], set);
	cpylen = ft_strlen(s1) - front - end;
	if (cpylen < 0)
	{
		cpylen = 0;
		return (0);
	}
	scpy = (char *)malloc(sizeof(char) * (cpylen + 1));
	if (scpy == NULL)
		return (NULL);
	ft_strlcpy(scpy, &s1[front], cpylen + 1);
	return (scpy);
}
