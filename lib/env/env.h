/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:20:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/22 21:43:07 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_sym_tab
{
	char				*var;
	struct s_sym_tab	*next;
}	t_sym_tab;

// our global var
t_sym_tab **g_sym_table;

// list operations
t_sym_tab	**init_sym_tab(char **envp);
t_sym_tab	*new_sym_tab_node(char *var);
int			get_list_len(t_sym_tab **head);
char		**create_env_list(t_sym_tab **head);
void		add_to_back(t_sym_tab **lst, t_sym_tab *new_node);

// exit status
void	init_exit_status(t_sym_tab **head);

#endif
