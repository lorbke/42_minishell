/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:59 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 14:03:23 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int builtin_echo(char **argv)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0 && ft_strlen(argv[i]) == 2)
		{
			i++;
			flag++;
		}
		while(argv[i])
		{
			while (ft_strncmp(argv[i], "-n", 2) == 0 && ft_strlen(argv[i]) == 2)
				i++;
			printf("%s", argv[i++]);
			if (argv[i])
				printf(" ");
		}
		if (!flag)
			printf("\n");
	}
	return (0);
}
