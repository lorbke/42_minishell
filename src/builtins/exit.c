/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:00:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 15:25:41 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_putstr_fd, ft_strjoin
#include <errno.h> // errno
#include <stdio.h> // printf
#include <unistd.h> // NULL
#include <string.h> // strerror

static int			is_num(char *str);
static long long	ft_atoi_long(char *str);
static void			print_to_stderr(char *str, char *arg);

int	builtin_exit(char **argv)
{
	int			argc;
	long long	exit_code;

	exit_code = errno;
	if (argv == NULL)
	{
		printf("exit\n");
		exit(exit_code % 256);
	}
	argc = 0;
	while(argv[argc] != NULL)
		argc++;
	printf("exit\n");
	if (argc == 2)
	{
		if (is_num(argv[1]))
			exit_code = ft_atoi_long(argv[1]) % 256;
		else
			print_to_stderr(NULL, argv[1]);
		exit(exit_code);
	}
	else if (argc > 2)
		print_to_stderr("too many arguments\n", NULL);
	return (0);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+' && str[i + 1] != '\0')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// check for over- and underflow
static int	check_value(long long number, int sign, char *str)
{
	number *= sign;
	if (number > 0 && sign == -1
	|| number < 0 && sign == 1)
	{
		print_to_stderr(NULL, str);
		return (-1);
	}
	return (number);
}

static long long	ft_atoi_long(char *str)
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
	number = check_value(number, sign, str);
	return (number);
}

static void	print_to_stderr(char *str, char *arg)
{
	if (str != NULL && arg != NULL)
	{
		ft_putstr_fd(ft_strjoin("minishell: exit: ", arg), STDERR_FILENO);
		ft_putstr_fd(ft_strjoin(":", str), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (str != NULL && arg == NULL)
		ft_putstr_fd(ft_strjoin("minishell: exit: ", str), STDERR_FILENO);
	else if (str == NULL && arg != NULL)
	{
		ft_putstr_fd(ft_strjoin("minishell: exit: ", arg), STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
}
