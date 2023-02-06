/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:50:47 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 09:56:19 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "executer.h"
#include <unistd.h>
#include <stdio.h>

int builtin_cd(char **argv)
{
	char *path;

	// in cd only the first argument is important; the rest gets more or less ignored
	path = argv[1];
	printf("inside my cd\n");
	printf("path: %s\n", path);
	if (chdir(path) != 0)
	{
		printf("Error\n");
		// @note need to handle this error properly
	}
	return (0);
}
