/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:14:08 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/18 20:52:51 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_frame_init(t_frame *frame, const char *format, va_list arg)
{
	va_copy(frame->arg, arg);
	va_end(arg);
	frame->format = format;
}

int	ft_printf(const char *format, ...)
{
	t_frame		frame;
	t_mods		mods;
	t_vector	vector;
	va_list		arg;

	va_start(arg, format);
	ft_frame_init(&frame, format, arg);
	ft_vector_init(&vector);
	ft_parse(&frame, &mods, &vector);
	return (ft_vector_get_len(&vector));
}
