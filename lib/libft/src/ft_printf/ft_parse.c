/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:53:45 by lorbke            #+#    #+#             */
/*   Updated: 2022/05/20 12:29:03 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_set_flags(t_frame *frame, t_mods *mods, int i)
{
	if (frame->format[i] == '+')
		mods->sign = 1;
	else if (frame->format[i] == ' ' && mods->sign == 0)
		mods->space = 1;
	else if (frame->format[i] == '0' && mods->field == 0
		&& mods->precision == 0)
		mods->field_char = '0';
	else if (frame->format[i] == '#')
		mods->hash = 1;
	else if (frame->format[i] >= '0' && frame->format[i] <= '9'
		&& mods->precision == 0)
			mods->field = mods->field * 10 + frame->format[i] - '0';
	else if (frame->format[i] >= '0' && frame->format[i] <= '9'
		&& mods->precision > 0)
		mods->field_prec = mods->field_prec * 10 + frame->format[i] - '0';
	else if (frame->format[i] == '.')
	{
		mods->field_char = ' ';
		mods->precision = 1;
	}
	else if (frame->format[i] == '-')
		mods->right = 1;
}

static void	ft_set_mods(t_mods *mods, const char c)
{
	if (c == 'p')
		mods->ptr = 1;
	if (c == 'X')
		mods->caps = 'X';
	if (c == 'p' || c == 'x' || c == 'X')
		mods->base = 16;
	if (mods->right == 0 && mods->space == 0
		&& mods->field > 0)
		mods->left = 1;
}

static void	ft_convert(t_frame *frame, t_mods *mods, t_vector *vector, int i)
{
	int	temp;

	ft_set_mods(mods, frame->format[i]);
	temp = ft_vector_get_len(vector) + mods->ptr * 2;
	if (frame->format[i] == 'i' || frame->format[i] == 'd')
		ft_itoa_printf(vector, mods, va_arg(frame->arg, int));
	else if (frame->format[i] == 'u')
		ft_itoa_printf(vector, mods, va_arg(frame->arg, unsigned int));
	else if (frame->format[i] == 'c')
		ft_printchar(vector, mods, va_arg(frame->arg, int));
	else if (frame->format[i] == 's')
		ft_printstr(vector, mods, va_arg(frame->arg, char *));
	else if (frame->format[i] == 'p')
		ft_itoa_printf(vector, mods, va_arg(frame->arg, unsigned long int));
	else if (frame->format[i] == 'x')
		ft_itoa_printf(vector, mods, va_arg(frame->arg, unsigned int));
	else if (frame->format[i] == 'X')
		ft_itoa_printf(vector, mods, va_arg(frame->arg, unsigned int));
	else if (frame->format[i] == '%')
		ft_printchar(vector, mods, '%');
	if (mods->right == 1)
		ft_vector_push_back(vector, ' ', mods->field
			- (ft_vector_get_len(vector) - temp));
}

void	ft_mods_init(t_mods *mods)
{
	mods->sign = 0;
	mods->len = 0;
	mods->ptr = 0;
	mods->base = 10;
	mods->caps = 'x';
	mods->hash = 0;
	mods->space = 0;
	mods->zero = 0;
	mods->field = 0;
	mods->field_char = ' ';
	mods->precision = 0;
	mods->field_prec = 0;
	mods->right = 0;
	mods->left = 0;
	mods->nbr_len = 0;
}

void	ft_parse(t_frame *frame, t_mods *mods, t_vector *vector)
{
	const char	*conv;
	int			i;

	conv = "cspdiouxX%";
	i = 0;
	while (frame->format[i] != 0)
	{
		ft_mods_init(mods);
		while (frame->format[i] != '%' && frame->format[i] != 0)
			ft_vector_push_back(vector, frame->format[i++], 1);
		if (frame->format[i] != 0)
			i++;
		while (ft_strchr(conv, frame->format[i]) == NULL
			&& frame->format[i] != 0)
			ft_set_flags(frame, mods, i++);
		if (frame->format[i] != 0)
			ft_convert(frame, mods, vector, i++);
	}
	write(1, ft_vector_get_output(vector), ft_vector_get_len(vector));
	ft_vector_free(vector);
}
