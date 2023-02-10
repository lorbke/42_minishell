/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/10 18:11:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "shinimell"
# define PROMPT "mini🐚~ "
# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

# define SIGNAL_STANDARD 0
# define SIGNAL_NOTHEREDOC 1
# define SIGNAL_HEREDOC 2

void	init_signals(char mode);
void	error_parse_print(int desc, char *error_loc);

#endif
