/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:59 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 11:01:52 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h" // ft_strcmp
#include <stdio.h> // ft_printf

int builtin_echo(char **argv)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		{
			i++;
			flag++;
		}
		while (argv[i])
		{
			printf("%s", argv[i]);
			if (argv[i])
				printf(" ");
			i++;
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}
