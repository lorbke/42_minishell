/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 09:24:55 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symtab.h"
#include "env.h"

void	builtin_env(t_sym_tab **sym_table) {
	char **env_list = create_env_list(sym_table);
	while (*env_list) {
		printf("%s\n", *env_list);
		env_list++;
	}
}
