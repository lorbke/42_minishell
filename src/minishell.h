/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/01/21 16:10:19 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR -1
# define PROMPT "shinimell 👽 "

# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

void	ms_init_signals(void);

#endif
