/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:37:28 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 13:38:53 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_PRIVATE_H
# define EXPORT_PRIVATE_H

# include "env.h"

// builtin_export_utils
char	*init_var_name(char *var);
char	*init_var_value(char *var, char *var_name);
int		update_if_exists(char *var_name, char *var_value);
int		check_if_var_exists(t_sym_tab *temp, char *var_name);

#endif
