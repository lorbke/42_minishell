/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 21:58:34 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include "libft.h" // ft_putstr_fd
#include "../utils.h" // free_split
#include <stdio.h> // printf

static void	print_error_msg(char *str);

int	env_b(char **argv)
{
	int	i;
	char **env_list;

	if (argv[1] != NULL)
	{
		print_error_msg(argv[1]);
		return (127);
	}
	env_list = create_env_list(g_sym_table);
	if (env_list == NULL)
	{
		ft_putstr_fd("env: couldn't fetch env\n", 2);
		return (-1);
	}
	i = 0;
	while (env_list[i] != NULL) {
		printf("%s\n", env_list[i]);
		i++;
	}
	free_split(env_list);
	return (0);
}

static void	print_error_msg(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
