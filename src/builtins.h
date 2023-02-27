/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:33:34 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/27 15:07:58 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "executer.h" // t_cmd_table
#include "../../lib/env/env.h"
#include <stdlib.h>

int	cd_b(char **argv);
int	pwd_b(char **argv);
int	env_b(char **argv);
int	echo_b(char **argv);
int	builtin_exit_b(char **argv);
int	unset_b(char **argv);
int	export_b(char **argv);
int	builtin_is_builtin(char *cmd);
int	builtin_exec(t_cmd_table *cmd_table);

#endif
