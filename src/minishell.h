/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/28 19:32:57 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h" // t_ast
# include <sys/types.h> // pid_t

# define SHELL_NAME "minishell"
# define PROMPT "minishell> "
# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

# define RETURN_ERROR -1

# define ERR_SUCCESS 0
# define ERR_GENERAL 1
# define ERR_SYNTAX 2
# define ERR_NOPERM 126
# define ERR_CMDNOTFOUND 127
# define ERR_SIGNAL 128

typedef unsigned char	t_status;

char		*ms_digest_input(char *input);
void		ms_print_syntax_error(int desc, char *error_loc);
void		ms_print_exec_error(t_status exit_status, char *error_loc);
void		ms_print_errno(char *error_loc);
void		ms_wait_pid_and_set_exit(pid_t pid);
void		ms_exit_status_set(t_status exit_status);
t_status	ms_exit_status_get(void);

#endif
