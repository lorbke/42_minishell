/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:17:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 13:59:25 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // t_sym_tab
#include "libft.h" // free, ft_isalpha, ft_isalnum
#include "../utils.h" // free_split, free_list, ft_perror, ft_strcmp
#include <stdio.h> // perror

void	free_split(char **split)
{
	int		i;
	char	**temp;

	if (split == NULL)
		return ;
	i = 0;
	temp = split;
	while (temp[i] != NULL)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	check_naming_convention(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '\0' && (ft_isalpha(var[i]) || var[i] == '_'))
	{
		while (var[i] != '\0' && (ft_isalnum(var[i]) || var[i] == '_'))
			i++;
	}
	if (i == 0)
		return (0);
	return (i);
}

int	get_string_array_len(char **array)
{
	int	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
