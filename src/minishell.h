/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/20 00:41:35 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h" // t_ast

# define SHELL_NAME "shinimell"
# define PROMPT "mini🐚~ "
# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

# define ERR_SUCCESS 0
# define ERR_GENERALERR 1 
# define ERR_SYNTAXERR 2
# define ERR_CMDNOTFOUND 127
# define ERR_SIGNAL 128

typedef unsigned char	t_status;

char	*digest_input(char *input, int fd_in, int fd_out);

#endif
