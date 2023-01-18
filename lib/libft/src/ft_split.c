/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 22:25:23 by lorbke            #+#    #+#             */
/*   Updated: 2022/08/07 20:11:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

static int	ft_getwordlen(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i] != 0)
	{
		j++;
		i++;
	}
	return (j);
}

static int	ft_mallocword(char **split, int word, int j)
{
	split[word] = (char *)malloc(sizeof(char) * (j + 1));
	if (split[word] == NULL)
	{
		while (word >= 0)
		{
			free(((void **)split)[word]);
			word--;
		}
		free((void **)split);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word;
	int		i;

	if (s == NULL)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * ((ft_countwords(s, c) + 1)));
	if (split == NULL)
		return (NULL);
	word = 0;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] == 0)
			break ;
		if (ft_mallocword(split, word, ft_getwordlen(s, c, i)) == 0)
			return (NULL);
		ft_strlcpy(&*split[word++], &s[i], ft_getwordlen(s, c, i) + 1);
		i += ft_getwordlen(s, c, i);
	}
	split[word] = 0;
	return (split);
}
