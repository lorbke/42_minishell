/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_entries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:14:13 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/11 21:29:30 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // malloc, ft_strlne, ft_strlcpy, ft_strjoin

static char	**add_to_beginning(char **result, char *entry, int i, int len);
static char		**add_to_end(char **result, char *entry, int i, int len);
static char		**add_to_mid(char **result, char *entry, int i, int len);

char	**sort_matching_entries(char **result, char *entry)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	len = 0;
	while (result[len])
		len++;
	j = 0;
	while (entry[j] == result[i][j])
		j++;
	if (entry[j] < result[i][j])
		result = add_to_beginning(result, entry, i, len);
	while (entry[j] > result[i][j])
	{
		i++;
		if (result[i] == NULL)
			break ;
	}
	if (result[i] == NULL)
		result = add_to_end(result, entry, i, len);
	else
		result = add_to_mid(result, entry, i, len);
	return (result);
}

static char	**add_to_beginning(char **result, char *entry, int i, int len)
{
	result[len] = malloc(sizeof(char) * ft_strlen(result[len - 1]));
	while (i < len)
	{
		result[len] = result[len - 1];
		len--;
	}
	result[i] = malloc(sizeof(char) * ft_strlen(entry));
	ft_strlcpy(result[i], entry, ft_strlen(entry) + 2);
	return (result);
}

static char	**add_to_mid(char **result, char *entry, int i, int len)
{
	result[len] = malloc(sizeof(char) * ft_strlen(result[len - 1]));
	while (i < len)
	{
		result[len] = result[len - 1];
		len--;
	}
	result[i] = malloc(sizeof(char) * ft_strlen(entry));
	ft_strlcpy(result[i], entry, ft_strlen(entry) + 2);
	return (result);
}

static char	**add_to_end(char **result, char *entry, int i, int len)
{
	result[len] = malloc(sizeof(char) * ft_strlen(entry));
	ft_strlcpy(result[len], entry, ft_strlen(entry) + 2);
	result[len + 1] = NULL;
	return (result);
}
