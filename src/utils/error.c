/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:08:00 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/18 14:11:25 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" // free, ft_strjoin, ft_strlcat, ft_strlen
#include "../utils.h" // ft_realloc
#include <stdio.h> // perror

void	ft_perror(char *cmd, char *str)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: ", cmd);
	error_msg = ft_realloc(error_msg, ft_strlen(error_msg) + 3);
	ft_strlcat(error_msg, ": ", ft_strlen(error_msg) + 3);
	error_msg = ft_realloc(error_msg, ft_strlen(error_msg) + ft_strlen(str) + 1);
	ft_strlcat(error_msg, str, ft_strlen(error_msg) + ft_strlen(str) + 1);
	perror(error_msg);
	free(error_msg);
}
