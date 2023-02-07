/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/07 15:20:26 by fyuzhyk          ###   ########.fr       */
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
