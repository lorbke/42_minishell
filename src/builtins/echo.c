/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:59 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/16 13:48:16 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h" // ft_strcmp
#include <stdio.h> // printf

int builtin_echo(char **argv)
{
	int i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (argv[i] != NULL)
	{
		while (argv[i] != NULL && ft_strcmp(argv[i], "-n") == 0)
		{
			i++;
			n_flag++;
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
