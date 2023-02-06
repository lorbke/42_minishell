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

#include "../../lib/env/env.h"
#include "executer.h"
#include <stdlib.h>

typedef struct	s_builtin
{
	char	*name;
	int		(*func)();
}	t_builtin;

// @note all builtins need to receive the same arguments
// if the env is global, it is enough to pass cmd_table->cmd
int	builtin_pwd(void);
int	builtin_cd(char **argv);
int	builtin_echo(char **argv);
int	builtin_env(t_sym_tab **sym_table);
int	builtin_unset(char *var, t_sym_tab **sym_table);
int	builtin_export(t_sym_tab **sym_table, char *name, char *value);
int	builtin_exit(char **argv);

const	t_builtin builtin_arr[] =
{
	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"pwd", &builtin_pwd},
	{"export", &builtin_export},
	{"unset", &builtin_unset},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
	//@note do we even need this?
	{NULL, NULL}
};

#endif
