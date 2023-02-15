/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:17:25 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/15 15:17:13 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" // g_sym_table
#include <stdio.h> // printf

int	builtin_env(char **argv) {
	int	i;

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
	i = 0;
	while (env_list[i]) {
		printf("%s\n", env_list[i]);
		i++;
	}
	return (0);
}
