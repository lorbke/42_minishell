/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:59 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 16:11:12 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strncmp, ft_strlen
#include "../utils.h" // ft_strcmp
#include <stdio.h> // printf

static int	check_for_flag(char *arg);

int	echo_b(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (argv[i] != NULL)
	{
		while (argv[i] != NULL && ft_strncmp(argv[i], "-n", 2) == 0)
		{
			n_flag = check_for_flag(argv[i]);
			if (n_flag == 0)
				break ;
			i++;
		}
		while (argv[i] != NULL)
		{
			printf("%s", argv[i]);
			i++;
			if (argv[i])
				printf(" ");
		}
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

static int	check_for_flag(char *arg)
{
	int	i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			break ;
		i++;
	}
	if (arg[i] != '\0')
		return (0);
	else
		return (1);
}
