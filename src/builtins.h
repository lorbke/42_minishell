/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:33:34 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/13 13:49:45 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../lib/executer/executer.h"
#include "../../lib/env/env.h"
#include <stdlib.h>

int	builtin_cd(char **argv);
int	builtin_pwd(char **argv);
int	builtin_env(char **argv);
int	builtin_echo(char **argv);
int	builtin_exit(char **argv);
int	builtin_unset(char **argv);
int	builtin_export(char **argv);
int	is_builtin(char *cmd);
int	exec_builtin(t_cmd_table *cmd_table);

#endif
