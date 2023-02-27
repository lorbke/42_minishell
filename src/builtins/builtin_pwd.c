/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:45:14 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 15:09:43 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // ft_strjoin
#include "../utils.h" // ft_perror
#include <stdio.h> // printf
#include <errno.h> // errno
#include <unistd.h> // getcwd
#include <limits.h> // PATH_MAX

int	pwd_b(char **argv)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		ft_perror("pwd", cwd);
		return (errno);
	}
	return (0);
}
