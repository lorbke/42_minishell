/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:20:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/28 13:59:03 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h> // bool

typedef struct s_sym_tab
{
	char				*var;
	struct s_sym_tab	*next;
}	t_sym_tab;

// global var
t_sym_tab	**g_sym_table;

// env_symtab
t_sym_tab	**init_sym_tab(char **envp);
t_sym_tab	*new_sym_tab_node(char *var);
void		init_exit_status(t_sym_tab **head);
void		env_free_sym_tab(t_sym_tab **head);

// env_utils
char		*get_value(char *var);
char		**create_env_list(t_sym_tab **head);
bool		env_is_var_value(char *var, char *value);

// env_symtab_utils
char		*increase_shlvl(char *shlvl);
int			get_list_len(t_sym_tab **head);
void		add_to_back(t_sym_tab **lst, t_sym_tab *new_node);
t_sym_tab	*copy_node(t_sym_tab *node);
t_sym_tab	*get_last_node(t_sym_tab *lst);

#endif
