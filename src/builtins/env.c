/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/07 11:06:43 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>

extern t_sym_tab	**g_sym_table;

int	builtin_env(char **argv) {
	char **env_list = create_env_list(g_sym_table);
	if (env_list == NULL)
	{
		printf("minishell: env: couldn't fetch env\n");
		return (-1);
	}
	if (argv[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", argv[1]);
		return (-1);
	}
	while (*env_list) {
		printf("%s\n", *env_list);
		env_list++;
	}
	return (0);
}
