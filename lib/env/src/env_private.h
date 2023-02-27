/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:27:02 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 16:54:39 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PRIVATE_H
# define ENV_PRIVATE_H

# include "env.h" // t_sym_tab

t_sym_tab	*copy_node(t_sym_tab *node);
t_sym_tab	*get_last_node(t_sym_tab *lst);

#endif
