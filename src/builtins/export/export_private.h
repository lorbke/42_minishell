/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:37:28 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 17:39:56 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_PRIVATE_H
# define EXPORT_PRIVATE_H

#include "env.h"

char	*init_var_name(char *var);
char	*init_var_value(char *var, char *var_name);
int		check_if_var_exists(t_sym_tab *temp, char *var_name);
void	update_var(t_sym_tab *temp, char *var_name, char *var_value);

#endif
