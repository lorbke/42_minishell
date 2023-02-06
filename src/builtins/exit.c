/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:00:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 17:19:36 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int			is_num(char *str);
long long 	ft_atoi_long(const char *str);

// argv in this case is cmd_table->cmd
void	builtin_exit(char **argv)
{
	int			argc;
	long long	exit_code;

	argc = 0;
	while(argv[argc])
		argc++;
	// exit w/o args called
	if (argc == 1)
	{
		//@note need to find the correct (current) exit code
		printf("exit\n");
		exit(exit_code % 256);
	}
	// exit with arg called
	else if (argc == 2)
	{
		// check whether the arg is a number
		// if so, convert via ft_atoi_long
		if (is_num(argv[1]))
		{
			exit_code = ft_atoi_long(argv[1]) % 256;
			printf("exit\n");
			exit(exit_code);
		}
		else
		{
			printf("exit\n");
			// print error message: numeric argument required
		}
	}
	else if (argc > 2)
	{
		//@note does not execute exit, but the first argument is set to be the new exit status (of the calling process)
		printf("exit\n");
		// print error message: too many arguments
	}
	exit(0);
}

int	is_num(char *str)
{
	int	i;
	int	c;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+' && str[i + 1] != '\0')
		i++;
	while (str[i])
	{
		// convert char to int
		c = str[i] - '0';
		if (!ft_isdigit(c))
			return (0);
	}
	return (1);
}

static int	check_flow(long long number, int sign)
{
	number *= sign;
	// check for underflow
	if (number > 0 && sign == -1)
		return (1);
	// check for overflow
	if (number < 0 && sign == 1)
		return (1);
	return (0);
}

long long 	ft_atoi_long(const char *str)
{
	int	i;
	int	sign;
	long long number;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13 && str[i] != 0) || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	// if overflow or underflow, need to exit approtiately instead of simply returning -1
	if (check_flow(number, sign))
		return (-1);
	return (number * sign);
}
