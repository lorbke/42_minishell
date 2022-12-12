/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:32:55 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/12 16:41:21 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEBUG_H
# define MS_DEBUG_H

# include <stdio.h>
# include <stdlib.h>
#include <termios.h>

# ifdef DEBUG
#  define DEBUG_MS 1
# else
#  define DEBUG_MS 0
# endif

void	debug_print_termios(struct termios *termios);

#endif
