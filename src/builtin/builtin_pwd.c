/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:45:14 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 21:12:01 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strjoin
#include "../utils.h" // ft_perror
#include <stdio.h> // printf
#include <errno.h> // errno
#include <unistd.h> // getcwd
#include <limits.h> // PATH_MAX

/**
 * It prints the current working directory
 * 
 * @param argv The arguments passed to the command.
 * 
 * @return The current working directory.
 */
int	pwd_b(char **argv)
{
	char	cwd[PATH_MAX];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		ft_perror("pwd", cwd);
		return (errno);
	}
	return (0);
}
