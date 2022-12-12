/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:31:40 by lorbke            #+#    #+#             */
/*   Updated: 2022/12/12 16:58:41 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugging.h"

/* Debug function to print the terminal settings. */
void	debug_print_termios(struct termios *termios)
{
	if (DEBUG_MS)
	{
		printf("termios:\n");
		printf("	input mode: %lx\n", termios->c_iflag);
		printf("	output mode: %lx\n", termios->c_oflag);
		printf("	control mode: %lx\n", termios->c_cflag);
		printf("	local mode: %lx\n", termios->c_lflag);
		printf("	control characters: %hhu\n", termios->c_cc[VQUIT]);
		printf("	input speed: %lu\n", termios->c_ispeed);
		printf("	output speed: %lu\n", termios->c_ospeed);
	}
}
