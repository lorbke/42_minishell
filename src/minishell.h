/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:39:03 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/11 23:38:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <signal.h>
# include <termios.h>

# define ERROR -1
# define PROMPT "minishell> "
# define EXIT "exit"

// not needed, but useful for reference
// struct s_termios
// {
// 	tcflag_t	c_iflag;  /* input modes */
// 	tcflag_t	c_oflag;  /* output modes */
// 	tcflag_t	c_cflag;  /* control modes */
// 	tcflag_t	c_lflag;  /* local modes */
// 	cc_t		c_cc[NCCS];  /* control characters (advanced terminal customization) */
//	speed_t		c_ispeed; /* input speed */
//	speed_t		c_ospeed; /* output speed */
// };

void	ms_init_signals(void);

#endif
