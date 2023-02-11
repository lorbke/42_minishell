/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2023/02/11 16:43:06 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h" // t_ast

# define SHELL_NAME "shinimell"
# define PROMPT "mini🐚~ "
# define CMD_SEPS " \t\n\r"
# define CMD_ESCS "\'\"()"

t_ast	*input_to_ast(char *input);
char	process_input(char *input, int fd_in, int fd_out);

#endif
