/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:33:34 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/21 18:47:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "executer.h" // t_cmd_table
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
