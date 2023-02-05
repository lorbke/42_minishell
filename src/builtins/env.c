/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/05 18:18:24 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

// @note this needs to be put in a symtab header later on
typedef struct s_sym_tab
{
	char				*name;
	char				*value;
	struct s_sym_tab	*next;
} t_sym_tab;

void	builtin_env(t_sym_tab **sym_table) {
	char **env_list = create_env_list(sym_table);
	while (*env_list) {
		printf("%s\n", *env_list);
		env_list++;
	}
}
