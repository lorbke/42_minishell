/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:07:29 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/04 22:10:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "libft.h"
# include "ft_vector.h"

typedef struct s_frame
{
	const char	*format;
	va_list		arg;
}	t_frame;

typedef struct s_mods
{
	int	sign;
	int	len;
	int	caps;
	int	ptr;
	int	base;
	int	hash;
	int	space;
	int	zero;
	int	field_char;
	int	field;
	int	precision;
	int	field_prec;
	int	right;
	int	left;
	int	nbr_len;
}	t_mods;

int		ft_printf(const char *format, ...);
void	ft_parse(t_frame *frame, t_mods *mods, t_vector *vector);

void	ft_itoa_printf(t_vector *vector, t_mods *mods, long int n);
void	ft_printstr(t_vector *vector, t_mods *mods, char *s);
void	ft_printchar(t_vector *vector, t_mods *mods, char c);

#endif
