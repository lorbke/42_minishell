/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 10:00:30 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/24 17:54:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" // ms_exit_status_set
#include "libft.h" // ft_putstr_fd, ft_strjoin
#include "../utils.h" // free_list
#include "env.h" // g_sym_table
#include "garbage_collector.h" // gc_free_all_garbage
#include <errno.h> // errno
#include <stdio.h> // printf
#include <unistd.h> // NULL
#include <string.h> // strerror

static int			is_num(char *str);
static void			exit_non_numeric(char **argv);
static long long	ft_atoi_long(char *str);

int	builtin_exit_b(char **argv)
{
	int			argc;
	long long	exit_code;

	exit_code = ms_exit_status_get();
	argc = get_string_array_len(argv);
	ft_putstr_fd("exit\n", STDIN_FILENO);
	if (argc >= 2)
	{
		if (is_num(argv[1]) == 0)
			exit_non_numeric(argv);
		else if (argc == 2)
			exit_code = ft_atoi_long(argv[1]) % 256;
		else if (argc > 2)
		{
			exit_print_to_stderr("too many arguments\n", NULL);
			ms_exit_status_set(1);
			exit_code = ms_exit_status_get();
			return (exit_code);
		}
	}
	gc_free_all_garbage();
	free_list(g_sym_table);
	exit(exit_code);
}

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[i] == '\0')
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
		exit_print_to_stderr(NULL, str);
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

static void	exit_non_numeric(char **argv)
{
	long long	exit_code;

	exit_print_to_stderr(NULL, argv[1]);
	exit_code = ms_exit_status_get();
	gc_free_all_garbage();
	free_list(g_sym_table);
	exit(exit_code);
}
