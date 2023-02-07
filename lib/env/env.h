/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 09:20:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 14:27:07 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_sym_tab
{
	char				*name;
	char				*value;
	struct s_sym_tab	*next;
}	t_sym_tab;

t_sym_tab	**init_sym_tab(char **envp);
char		**create_env_list(t_sym_tab **head);

#endif
