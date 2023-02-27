/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:08:00 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 16:49:27 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_putstr_fd
#include "../utils.h" // ft_realloc
#include "../minishell.h" // ms_exit_status_set
#include <stdio.h> // perror

void	ft_perror(char *cmd, char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(str);
}

void	exit_print_to_stderr(char *str, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (str != NULL && arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ms_exit_status_set(1);
	}
	else if (str != NULL && arg == NULL)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ms_exit_status_set(1);
	}
	else if (str == NULL && arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		ms_exit_status_set(255);
	}
}
