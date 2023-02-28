/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:57:59 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:37:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strncmp, ft_strlen
#include "../utils.h" // utils_ft_strcmp
#include <stdio.h> // printf

static int	check_for_flag(char *arg);

/**
 * It prints out the arguments passed to it, with a space between each 
 * argument, and a newline at the end, unless the -n flag is passed
 * 
 * @param argv The array of arguments passed to the program.
 * 
 * @return The return value is the exit status of the program.
 */
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

/**
 * It checks if the argument is a flag
 * 
 * @param arg The argument that is being checked.
 * 
 * @return the number of flags that are present in the argument.
 */
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
