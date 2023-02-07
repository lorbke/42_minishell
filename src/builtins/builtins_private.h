/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:32:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 11:39:43 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_PRIVATE_H
# define BUILTINS_PRIVATE_H

#include "../builtins.h"
#include "libft.h"

typedef struct	s_builtin
{
	char	*name;
	int		(*func)(char **argv);
}	t_builtin;

const	t_builtin builtin_arr[] =
{
	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"pwd", &builtin_pwd},
	{"export", &builtin_export},
	{"unset", &builtin_unset},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
	//@note do we even need this?
	{NULL, NULL}
};

#endif
