/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:27:02 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/08 11:44:52 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
# define SYMTAB_H

#include "env.h"

t_sym_tab	*copy_node(t_sym_tab *node);
t_sym_tab	*get_last_node(t_sym_tab *lst);

#endif
