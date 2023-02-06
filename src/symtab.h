/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:27:02 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/05 18:36:07 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMTAB_H
# define SYMTAB_H

#include <stdio.h>
#include <stdlib.h>

typedef struct s_sym_tab
{
	char				*name;
	char				*value;
	struct s_sym_tab	*next;
}	t_sym_tab;

t_sym_tab	**init_sym_tab(char **envp);
t_sym_tab	*copy_node(t_sym_tab *node);
t_sym_tab	*get_last_node(t_sym_tab *lst);
t_sym_tab	*env_to_sym_tab_node(char *env);
t_sym_tab	*new_sym_tab_node(char *name, char *value);
int			get_list_len(t_sym_tab **head);
void		add_to_back(t_sym_tab **lst, t_sym_tab *new_node);

#endif
