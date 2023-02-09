/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/09 14:34:01 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1
# define SHELL_NAME "shinimell"
# define PROMPT "mini🐚~ "

# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

void	ms_init_signals(void);
void	error_exec_print(char exit_status, char *error_loc);
void	error_parse_print(int desc, char *error_loc);

#endif
