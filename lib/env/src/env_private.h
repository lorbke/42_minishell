/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:27:02 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 20:25:19 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_PRIVATE_H
# define ENV_PRIVATE_H

# include "env.h" // t_sym_tab

// env_symtab_utils
t_sym_tab	*env_copy_node(t_sym_tab *node);
t_sym_tab	*get_last_node(t_sym_tab *lst);
char		*increase_shlvl(char *shlvl);
int			get_list_len(t_sym_tab **head);

#endif
