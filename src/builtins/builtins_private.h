/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_private.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:32:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 14:49:35 by fyuzhyk          ###   ########.fr       */
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

#endif
