/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror_and_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:14:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 20:38:17 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // exit
#include <stdio.h> // perror
#include <sys/errno.h> // errno

/* Prints an error message and calls exit with errno. */
void	ft_perror_and_exit(char *msg)
{
	perror(msg);
	exit(errno);
}
