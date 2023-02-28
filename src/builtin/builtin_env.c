/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:11:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" // RETURN_ERROR
#include "env.h" // g_sym_table
#include "libft.h" // ft_putstr_fd
#include "../utils.h" // free_split
#include <stdio.h> // printf

static void	print_error_msg(char *str);

/**
 * It prints the environment variables
 * 
 * @param argv the arguments passed to the command
 * 
 * @return The return value of the last command executed.
 */
int	env_b(char **argv)
{
	int		i;
	char	**env_list;

	if (argv[1] != NULL)
	{
		print_error_msg(argv[1]);
		return (127);
	}
	env_list = create_env_list(g_sym_table);
	if (env_list == NULL)
	{
		ft_putstr_fd("env: couldn't fetch env\n", 2);
		return (RETURN_ERROR);
	}
	i = 0;
	while (env_list[i] != NULL)
	{
		printf("%s\n", env_list[i]);
		i++;
	}
	free_split(env_list);
	return (0);
}

/**
 * It prints an error message to the standard error output
 * 
 * @param str The string to print
 */
static void	print_error_msg(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
