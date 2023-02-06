/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:33:34 by fyuzhyk           #+#    #+#             */
/*   Updated: 2023/02/06 17:50:56 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

void	builtin_pwd(void);
void	builtin_cd(char *path);
void	builtin_exit(char **argv);
void	builtin_echo(char **argv);
void	builtin_env(t_sym_tab **sym_table);
void	builtin_unset(char *var, t_sym_tab **sym_table);
void	builtin_export(t_sym_tab **sym_table, char *name, char *value);

#endif
